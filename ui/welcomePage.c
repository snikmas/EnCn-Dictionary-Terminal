#include "ascii.h"

char *welcome_title = "WELCOME TO TERMINAL";
static char *mascot[] = {
    "   (\\_._/)",
    "   ( ^ ^ )   System Online.",
    "   /  V  \\   Dictionary Booting...",
    "  /(  _  )\\",
    "   ^^   ^^"
};
static int mascot_lines = sizeof(mascot) / sizeof(mascot[0]);

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
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);  // terminal size
    clear();                       // clear previous screen

    int menuWidth = (xMax < 50) ? xMax - 4 : 50;  // avoid overflow

    // Title Window
    WINDOW *titleWin = newwin(3, menuWidth, 1, (xMax - menuWidth) / 2);
    box(titleWin, 0, 0);
    mvwprintw(titleWin, 1, (menuWidth - strlen(welcome_title)) / 2, "%s", welcome_title);
    wrefresh(titleWin);

    // Mascot Window
    WINDOW *mascotWin = newwin(mascot_lines + 2, menuWidth, 5, (xMax - menuWidth) / 2);
    box(mascotWin, 0, 0);
    for (int i = 0; i < mascot_lines; i++) {
        mvwprintw(mascotWin, i + 1, 2, "%s", mascot[i]);
        wrefresh(mascotWin);
        usleep(150000); // smooth animation
    }

    // Loading Window
    WINDOW *loadingWin = newwin(3, menuWidth, 5 + mascot_lines + 2, (xMax - menuWidth) / 2);
    box(loadingWin, 0, 0);
    mvwprintw(loadingWin, 0, 2, "Loading...");
    wrefresh(loadingWin);

    int barWidth = menuWidth - 10;
    for (int i = 0; i <= 100; i += 10) {
        draw_loading(loadingWin, 1, 2, barWidth, i);
        usleep(200000);
    }

    mvwprintw(loadingWin, 2, 2, "Press any key to continue...");
    wrefresh(loadingWin);
    wgetch(loadingWin);  // wait for user
    getch();

    // Clean up windows
    delwin(titleWin);
    delwin(mascotWin);
    delwin(loadingWin);
    clear();   // ready for next page
    refresh();
}
