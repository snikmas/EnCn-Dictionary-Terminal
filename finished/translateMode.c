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
    box(titleWin, 0, 0);
    mvwprintw(titleWin, 2, (PROGRAM_WIDTH - (int)strlen(page_titles[0])) / 2, "%s", page_titles[0]);
    mvwprintw(titleWin, 3, (PROGRAM_WIDTH - (int)strlen(page_titles[1 + mode])) / 2, "%s", page_titles[1 + mode]);
    wrefresh(titleWin);

    /* ---------------- Mascot Window ---------------- */
    int titleH, titleW;
    getmaxyx(titleWin, titleH, titleW);

    WINDOW *mascotWin = newwin(LINES_MASCOT + 2, PROGRAM_WIDTH - 4, titleH, startX + 2);
    for (int i = 0; i < LINES_MASCOT; i++) {
        mvwprintw(mascotWin, i + 1, 1, "%s", mascots[0][i]);
    }
    wrefresh(mascotWin);

    int mascotH, mascotW;
    getmaxyx(mascotWin, mascotH, mascotW);

    /* ---------------- Input Window ---------------- */
    int inputH = 7;
    int inputY = titleH + mascotH + 1;
    WINDOW *inputWin = newwin(inputH, PROGRAM_WIDTH, inputY - 1, startX);

    char *prompt = (mode == 0) ? "Enter English Word: " : "Enter Chinese Word: ";
    mvwprintw(inputWin, 1, 2, "%s", prompt);
    curs_set(1);
    echo();

    char *input = malloc(100);
    Word *newWord = malloc(sizeof(Word));
    if (!input || !newWord) {
        handleErrors(ERR_OUT_OF_MEMORY, "translateMode");
    }

    wmove(inputWin, 1, (int)strlen(prompt) + 2);
    wgetnstr(inputWin, input, 99);
    wrefresh(inputWin);

    if (strlen(input) > 0) {
        mvwprintw(inputWin, 3, 2, "Processing translation...");
        wrefresh(inputWin);
        noecho();
        curs_set(0);
    }
    makeRequest(mode, newWord, input);

    /* ---------------- Loading Bar Window ---------------- */
    int loadY = inputY + inputH - 5;
    WINDOW *loadWin = newwin(3, PROGRAM_WIDTH, loadY, startX);
    // Move "Loading..." text to y = 0 to avoid overlap with the bar
    mvwprintw(loadWin, 0, 2, "Loading...");
    wrefresh(loadWin);

    for (int i = 0; i <= 100; i += 10) {
        draw_loading(loadWin, i);
        usleep(200000);
    }

    /* ---------------- Result Window ---------------- */
    int loadH, loadW;
    getmaxyx(loadWin, loadH, loadW);

    WINDOW *resultWin = newwin(6, loadW, loadY + loadH + 2, startX);
    box(resultWin, 0, 0);
    mvwprintw(resultWin, 2, 2, "Input: %s", input);

    if (mode == 0)
        mvwprintw(resultWin, 3, 2, "Translation: %s", newWord->wordCn);
    else
        mvwprintw(resultWin, 3, 2, "Translation: %s", newWord->wordEn);

    wrefresh(resultWin);

    actions("translateMode", mode, newWord);
    getch();

    /* ---------------- Cleanup ---------------- */
    delwin(titleWin);
    delwin(mascotWin);
    delwin(inputWin);
    delwin(loadWin);
    delwin(resultWin);
    free(input);
    free(newWord);

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