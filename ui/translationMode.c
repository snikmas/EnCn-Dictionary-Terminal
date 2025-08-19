#include <stdlib.h>
#include <ctype.h>

#include "ascii.h"

char *menus_items_1[] = {
    "EN - CN Dictionary",
    "EN -> CN Mode", 
    "CN -> EN Mode"
};

int items = sizeof(menus_items_1) / sizeof(menus_items_1[0]);

char *mascot_1[] = {
    "  (\\_._/)",
    "  ( ^ ^ )      Ready for input . . .",
    "  /  V  \\",
    " /(  _  )\\",
    "   ^^ ^^"
};

int mascot_1_lines = sizeof(mascot_1) / sizeof(mascot_1[0]);

void draw_loading_1(WINDOW *loadingWin, int y, int x, int width, int percent) {
    int fill = (percent * width) / 100;
    mvwprintw(loadingWin, y, x, "[");
    for (int i = 0; i < width; i++)
        waddch(loadingWin, (i < fill) ? '#' : '.');
    waddch(loadingWin, ']');
    wprintw(loadingWin, " %3d%%", percent);
    wrefresh(loadingWin);
}

void translateMode(int mode) {
    
    clear();
    refresh();
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);


    // Title window
    WINDOW *menuTitle = newwin(6, 40, 0, 0);
    mvwprintw(menuTitle, 2, 10, "%s", menus_items_1[0]);
    mvwprintw(menuTitle, 3, 12, "%s", menus_items_1[mode + 1]);
    box(menuTitle, 0, 0);
    wrefresh(menuTitle);

    // Mascot_1 window
    int heightMenu, widthMenu;
    getmaxyx(menuTitle, heightMenu, widthMenu);
    WINDOW *mascot_1Win = newwin(mascot_1_lines + 2, xMax - 4, heightMenu, 2);
    for (int i = 0; i < mascot_1_lines; i++)
        mvwprintw(mascot_1Win, i + 1, 1, "%s", mascot_1[i]);
    wrefresh(mascot_1Win);

    int heightMascot_1, widthMascot_1;
    getmaxyx(mascot_1Win, heightMascot_1, widthMascot_1);

    // Input window
    int menuHeight = items + 5;
    int menuWidth = 40;
    int menuStartY = heightMenu + heightMascot_1 + 1;
    int menuStartX = 0;

    WINDOW *inputWin = newwin(menuHeight, menuWidth, menuStartY - 1, menuStartX);
    echo();
    char *prompt = mode == 0 ? "Enter English Word: " : "Enter Chinese Word: ";
    mvwprintw(inputWin, 1, 2, "%s", prompt);
    curs_set(1);

    char input[99];
    wmove(inputWin, 1, strlen(prompt) + 2);
    wgetnstr(inputWin, input, sizeof(input) - 1);
    wrefresh(inputWin);

    if (strlen(input) > 0) {
        mvwprintw(inputWin, 3, 2, "Processing translation...");
        wrefresh(inputWin);
        noecho();
        curs_set(0);
    }

    // Loading bar
    int loadingStartY = menuStartY + menuHeight - 5;
    int loadingStartX = 0;
    WINDOW *loadingWin = newwin(3, menuWidth, loadingStartY, loadingStartX);
    wrefresh(loadingWin);
    int barWidth = menuWidth - 10;
    for (int i = 0; i <= 100; i += 10) {
        draw_loading_1(loadingWin, 1, 2, barWidth, i);
        usleep(200000);
    }

    // Result window
    int heightLoad, widthLoad;
    getmaxyx(loadingWin, heightLoad, widthLoad);
    WINDOW *resultWin = newwin(4, widthLoad, loadingStartY + heightLoad, 0);
    box(resultWin, 0, 0);

    // Show input and placeholder translation
    mvwprintw(resultWin, 1, 2, "Input: %s", input);
    if (mode == 0)
        mvwprintw(resultWin, 2, 2, "Translation: [EN -> CN result]");
    else
        mvwprintw(resultWin, 2, 2, "Translation: [CN -> EN result]");
    
    wrefresh(resultWin);

    // Wait before exit
    getch();
}
