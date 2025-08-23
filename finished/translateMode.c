#include "ascii.h"
#include "main.h"
#include "errors.h"
#include "word.h"
#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static void draw_loading(WINDOW *win, int percent);

void translateMode(int mode) {
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
    WINDOW *mascotWin = newwin(LINES_MASCOT + 2, PROGRAM_WIDTH - 4, titleWinH, startX + 2);
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
    int inputH = 7;
    int inputY = titleWinH + LINES_MASCOT + 1;
    WINDOW *inputWin = newwin(inputH, PROGRAM_WIDTH, inputY - 1, startX);
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
    
    if (!input || !newWord) {
        if (input) free(input);
        if (newWord) free(newWord);
        delwin(titleWin);
        delwin(mascotWin);
        delwin(inputWin);
        handleErrors(ERR_OUT_OF_MEMORY, "translateMode");
    }

    wmove(inputWin, 1, (int)strlen(prompt) + 2);
    wgetnstr(inputWin, input, 99);
    wrefresh(inputWin);

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
    delwin(loadWin);
    usleep(100000);

    /* ---------------- Result Window ---------------- */

    WINDOW *resultWin = newwin(4, PROGRAM_WIDTH, loadY + 2, startX);  // Reduced height from 6 to 4
    
    if (!resultWin) {
        // Handle window creation failure
        delwin(titleWin);
        delwin(mascotWin);
        delwin(inputWin);
        return;
    }
    box(resultWin, 0, 0);
    
    mvwprintw(resultWin, 1, 2, "Input: %s", input);

    if (mode == 0) {
        if (newWord->wordCn && strlen(newWord->wordCn) > 0) {
            mvwprintw(resultWin, 2, 2, "Translation: %s", newWord->wordCn);
        } else {
            mvwprintw(resultWin, 2, 2, "Translation: Translation failed");
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

    actions("translateMode", mode, newWord, nextY);
    // Remove the getch() call here as it interferes with the action menu

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