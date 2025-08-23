#include "ascii.h"
#include "main.h"
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

char *welcome_title = "WELCOME TO TERMINAL";

void draw_loading(WINDOW *win, int y, int x, int width, int percent);

void welcomePage() {
    clear();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // int PROGRAM_WIDTH = (xMax < 60) ? xMax - 2 : 60;
    int startX = (xMax - PROGRAM_WIDTH) / 2;

    // 1. Title Window
    WINDOW *titleWin = newwin(3, PROGRAM_WIDTH, 2, startX);
    if (!titleWin) return;
    
    // Draw box manually
    box(titleWin, 0, 0);
    
    int titleX = (PROGRAM_WIDTH - (int)strlen(page_titles[0])) / 2;
    mvwprintw(titleWin, 1, titleX, "%s", page_titles[0]);
    wrefresh(titleWin);

    // 2. Mascot Window
    int mascotHeight = LINES_MASCOT + 2;
    WINDOW *mascotWin = newwin(mascotHeight, PROGRAM_WIDTH, 6, startX);
    if (!mascotWin) {
        delwin(titleWin);
        return;
    }
    
    // Draw box manually
    box(mascotWin, 0, 0);

    // Вычисляем максимальную длину строки маскота для центрирования
    int maxMascotLen = 0;
    for (int i = 0; i < LINES_MASCOT; i++) {
        int len = strlen(mascots[0][i]);
        if (len > maxMascotLen) maxMascotLen = len;
    }

    for (int i = 0; i < LINES_MASCOT; i++) {
        int mascotX = (PROGRAM_WIDTH - (int)strlen(mascots[0][i])) / 2;
        mvwprintw(mascotWin, i + 1, mascotX, "%s", mascots[0][i]);
        wrefresh(mascotWin);
        usleep(120000);
    }

    // 3. Loading Window
    int loadingY = 6 + mascotHeight + 1;
    WINDOW *loadingWin = newwin(5, PROGRAM_WIDTH, loadingY, startX);
    if (!loadingWin) {
        delwin(titleWin);
        delwin(mascotWin);
        return;
    }
    
    // Draw box manually
    box(loadingWin, 0, 0);
    
    mvwprintw(loadingWin, 1, 2, "Loading...");
    wrefresh(loadingWin);

    int barWidth = PROGRAM_WIDTH - 10;
    for (int i = 0; i <= 100; i += 10) {
        draw_loading(loadingWin, 2, 2, barWidth, i);
        usleep(150000);
    }

    mvwprintw(loadingWin, 3, 2, "Press any key to continue...");
    wrefresh(loadingWin);
    wgetch(loadingWin);

    // Clean up
    delwin(titleWin);
    delwin(mascotWin);
    delwin(loadingWin);
    clear();
    refresh();
}


void draw_loading(WINDOW *win, int y, int x, int width, int percent) {
    int fill = (percent * width) / 100;
    mvwprintw(win, y, x, "[");
    for (int i = 0; i < width; i++)
        waddch(win, (i < fill) ? '#' : '.');
    waddch(win, ']');
    wprintw(win, " %3d%%", percent);
    wrefresh(win);
}
