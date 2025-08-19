#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#include "acsii.h"

char *welcome_title = "WELCOME TO TERMINAL";
char *mascot[] = {
    "   (\\_._/)",
    "   ( ^ ^ )   System Online.",
    "   /  V  \\   Dictionary Booting...",
    "  /(  _  )\\",
    "   ^^   ^^"
};
int mascot_lines = sizeof(mascot) / sizeof(mascot[0]);

void draw_loading(WINDOW *win, int y, int x, int width, int percent) {
    int fill = (percent * width) / 100;
    mvwprintw(win, y, x, "[");
    for (int i = 0; i < width; i++)
        waddch(win, (i < fill) ? '#' : '.');
    waddch(win, ']');
    wprintw(win, " %3d%%", percent);
    wrefresh(win);
}

void welcomePage() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    int menuWidth = 50;

    // Title Window
    WINDOW *titleWin = newwin(3, menuWidth, 0, (xMax - menuWidth) / 2);
    box(titleWin, 0, 0);
    mvwprintw(titleWin, 1, (menuWidth - strlen(welcome_title)) / 2, "%s", welcome_title);
    wrefresh(titleWin);

    // Mascot Window
    WINDOW *mascotWin = newwin(mascot_lines + 2, menuWidth, 4, (xMax - menuWidth) / 2);
    box(mascotWin, 0, 0);
    for (int i = 0; i < mascot_lines; i++) {
        mvwprintw(mascotWin, i + 1, 2, "%s", mascot[i]);
        wrefresh(mascotWin);
        usleep(150000);
    }

    // Loading Window
    WINDOW *loadingWin = newwin(3, menuWidth, 4 + mascot_lines + 2, (xMax - menuWidth) / 2);
    box(loadingWin, 0, 0);
    mvwprintw(loadingWin, 0, 2, "Loading...");
    wrefresh(loadingWin);

    int barWidth = menuWidth - 10;
    for (int i = 0; i <= 100; i += 10) {
        draw_loading(loadingWin, 1, 2, barWidth, i);
        usleep(200000);
    }

    mvwprintw(loadingWin, 2, 2, "Ready!");
    wrefresh(loadingWin);

    getch();
    endwin();
}
