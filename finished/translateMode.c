#include "ascii.h"
#include "main.h"
#include "errors.h"
#include "word.h"
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

static void draw_loading(WINDOW *win, int percent);

void translateMode(int mode) {

    setlocale(LC_ALL, "");
    int repeat = 1;

    while (repeat == 1){

    
    clear();
    refresh();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    int startX = (xMax - PROGRAM_WIDTH) / 2;
    if (startX < 0) startX = 0;

    /* ---------------- Title Window ---------------- */
    WINDOW *titleWin = newwin(6, PROGRAM_WIDTH, 0, startX);
    if (!titleWin) return;
    
    // Draw box manually
    box(titleWin, 0, 0);
    
    mvwprintw(titleWin, 2, (PROGRAM_WIDTH - (int)strlen(page_titles[0])) / 2, "%s", page_titles[0]);
    mvwprintw(titleWin, 3, (PROGRAM_WIDTH - (int)strlen(page_titles[1 + mode])) / 2, "%s", page_titles[1 + mode]);
    wrefresh(titleWin);

    int titleWinH = 6; // Define the title window height

    /* ---------------- Mascot Window ---------------- */
    WINDOW *mascotWin = newwin(LINES_MASCOT + 4, PROGRAM_WIDTH, titleWinH, startX);
    if (!mascotWin) {
        delwin(titleWin);
        return;
    }
    
    // Draw box manually
    box(mascotWin, 0, 0);
    
    for (int i = 0; i < LINES_MASCOT; i++) {
        mvwprintw(mascotWin, i + 1, 1, "%s", mascots[0][i]);
    }
    wrefresh(mascotWin);

    /* ---------------- Input Window ---------------- */
    int inputH = 9;
    int inputY = titleWinH + LINES_MASCOT + 3;
    WINDOW *inputWin = newwin(inputH, PROGRAM_WIDTH, inputY + 2, startX);
    if (!inputWin) {    
        delwin(titleWin);
        delwin(mascotWin);
        return;
    }
    
    // Draw box manually
    box(inputWin, 0, 0);

    char *prompt = (mode == 0) ? "Enter English Word: " : "Enter Chinese Word: ";
    mvwprintw(inputWin, 1, 2, "%s", prompt);
    curs_set(1);
    echo();

    char *input = malloc(100);
    Word *newWord = malloc(sizeof(Word));
    
    // Initialize Word structure to prevent segfaults
    if (newWord) {
        newWord->wordEn = NULL;
        newWord->wordCn = NULL;
        newWord->isFavorite = false;
    }

    while (!input || !newWord) {
        mvwprintw(inputWin, 1, 2, "Input the world!\n");
    }

    wmove(inputWin, 1, (int)strlen(prompt) + 2);
    wgetnstr(inputWin, input, 99);
    wrefresh(inputWin);

    // if cn-en and inputu in english
    // mode 0: en->cn, input in the english
    while (!( (unsigned char)input[0] < 128 && isalpha((unsigned char)input[0]) ) && mode == 0) {
        mvwprintw(inputWin, 3, 2, "You are in the En -> Cn mode! Please, use English!");
        wrefresh(inputWin);
        usleep(1500000);
        mvwprintw(inputWin, 3, 2, "                                                      ");

        // clean the line
        // очистка строки ввода
        wmove(inputWin, 1, (int)strlen(prompt) + 2);
        wclrtoeol(inputWin);
        wrefresh(inputWin);

        // очистка буфера input
        memset(input, 0, 100);

        // новый ввод
        wgetnstr(inputWin, input, 99);
    }

    // В режиме CN -> EN
    while (((unsigned char)input[0] < 128 && isalpha((unsigned char)input[0])) && mode == 1) {
        mvwprintw(inputWin, 3, 2, "You are in the Cn -> En mode! Please, use Chinese!");
        wrefresh(inputWin);
        usleep(1500000);
        mvwprintw(inputWin, 3, 2, "                                                      ");


         // clean the line
        // очистка строки ввода
        wmove(inputWin, 1, (int)strlen(prompt) + 2);
        wclrtoeol(inputWin);
        wrefresh(inputWin);

        // очистка буфера input
        memset(input, 0, 100);

        // новый ввод
        wgetnstr(inputWin, input, 99);
    }

    while (strlen(input) <= 1) {
        mvwprintw(inputWin, 3, 2, "Please, Input a word!");
        wrefresh(inputWin);
        usleep(1500000);
        mvwprintw(inputWin, 3, 2, "                                                      ");


         // clean the line
        // очистка строки ввода
        wmove(inputWin, 1, (int)strlen(prompt) + 2);
        wclrtoeol(inputWin);
        wrefresh(inputWin);

        // очистка буфера input
        memset(input, 0, 100);

        // новый ввод
        wgetnstr(inputWin, input, 99);
    }



    makeRequest(mode, newWord, input);
    if (strlen(input) > 0) {
        mvwprintw(inputWin, 3, 2, "Processing translation...");
        wrefresh(inputWin);
        noecho();
        curs_set(0);
        
        // Add to history if translation was successful
        if (newWord && newWord->wordEn && newWord->wordCn) {
            addToHistory(newWord);
        }
    }

    /* ---------------- Loading Bar Window ---------------- */
    int loadY = inputY + inputH - 5;
    WINDOW *loadWin = newwin(3, PROGRAM_WIDTH, loadY, startX);
    if (!loadWin) {
        delwin(titleWin);
        delwin(mascotWin);
        delwin(inputWin);
        return;
    }
    
    // Draw box manually
    box(loadWin, 0, 0);
    
    // Move "Loading..." text to y = 0 to avoid overlap with the bar
    // mvwprintw(loadWin, 0, 2, "Loading...");
    wrefresh(loadWin);

    for (int i = 0; i <= 100; i += 10) {
        draw_loading(loadWin, i);
        usleep(200000);
    }
    
    wclear(loadWin);
    wrefresh(loadWin); // added
    delwin(loadWin);
    usleep(100000);
    refresh();

    /* ---------------- Result Window ---------------- */

    WINDOW *resultWin = newwin(9, PROGRAM_WIDTH, loadY - 2, startX);  // Reduced height from 6 to 4
    
    if (!resultWin) {
        // Handle window creation failure
        delwin(titleWin);
        delwin(mascotWin);
        delwin(inputWin);
        return;
    }
    box(resultWin, 0, 0);
    
    mvwprintw(resultWin, 3, 2, "Input: %s", input);
    

    if (mode == 0) {
        if (newWord->wordCn && strlen(newWord->wordCn) > 0) {
            mvwprintw(resultWin, 4, 2, "Translation: %s", newWord->wordCn);
        } else {
            mvwprintw(resultWin, 7, 2, "Translation: Translation failed");
        }
    } else {
        if (newWord->wordEn && strlen(newWord->wordEn) > 0) {
            mvwprintw(resultWin, 2, 2, "Translation: %s", newWord->wordEn);
        } else {
            mvwprintw(resultWin, 2, 2, "Translation: Translation failed");
        }
    }
    
    wrefresh(resultWin);


    int nextY = loadY + 6;  // Increased from 4 to 6 to give more space

    int action_result = actions("translateMode", mode, newWord, nextY);
    
    /* ---------------- Cleanup ---------------- */
    delwin(titleWin);
    delwin(mascotWin);
    delwin(inputWin);
    delwin(resultWin);

    // Free allocated memory
    if (newWord) {
        if (newWord->wordEn) free(newWord->wordEn);
        if (newWord->wordCn) free(newWord->wordCn);
        free(newWord);
    }
    if (input) free(input);

    clear();
    refresh();
    if(action_result == 1){
        continue;
    } else {
        repeat = 0;
    }
    } 


}

/* ====================================================== */
/* Helper: centered loading bar                           */
/* ====================================================== */
static void draw_loading(WINDOW *win, int percent) {
    int h, w;
    getmaxyx(win, h, w);

    int barW = w - 10;
    if (barW < 10) barW = 10;

    int fill = (percent * barW) / 100;
    int y = h - 1; // Draw the bar at the bottom line of the window
    int barTotal = barW + 7;
    int x = (w - barTotal) / 2;
    if (x < 1) x = 1;

    // Clear only the line where the bar is drawn
    mvwhline(win, y, 0, ' ', w);
    mvwprintw(win, y, x, "[");
    for (int i = 0; i < barW; i++) {
        waddch(win, (i < fill) ? '#' : '.');
    }
    wprintw(win, "]");
    wprintw(win, " %3d%%", percent);

    // Redraw "Loading..." text at the top to ensure it persists
    mvwprintw(win, 0, 2, "Loading...");

    wrefresh(win);
}