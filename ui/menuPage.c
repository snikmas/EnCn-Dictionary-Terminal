#include <ncurses.h>
#include "ascii.h"

char *menus_items[] = {
  "EN - CN Dictionary",
  "Welcome, Hacker.\nTerminal Ready.",
  "MENU",
  "[1] Translate EN -> CN",
  "[2] Translate CN -> EN",
  "[3] Saved Translations",
  "[4] History",
  "[0] Exit",
};

int items = sizeof(menus_items) / sizeof(menus_items[0]) - 3;

char *mascot[] = {
        "  (\\_._/)",
        "  ( o o )      Welcome, Hacker.",
        "  /  V  \\      Terminal Ready.",
        " /(  _  )\\",
        "   ^^ ^^"
    };

int mascot_lines = sizeof(mascot) / sizeof(mascot[0]);


int menuPage() {
    noecho();           
    cbreak();          
    curs_set(0);       

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *menuTitle = newwin(5, 40, 0, 0);
    box(menuTitle, 0, 0);
    mvwprintw(menuTitle, 2, 10, menus_items[0]);
    refresh();
    wrefresh(menuTitle);

    int heightMenu, widthMenu;
    getmaxyx(menuTitle, heightMenu, widthMenu);
    WINDOW *mascotWin = newwin(mascot_lines + 2, xMax - 4, heightMenu, 2 );
    for(int i = 0; i < mascot_lines; i++)
        mvwprintw(mascotWin, i + 1, 1, "%s", mascot[i]);
    wrefresh(mascotWin);

    int menuHeight = items + 2;
    int menuWidth = 40;
    int menuStartY = heightMenu + mascot_lines + 1;
    int menuStartX = 0;

    WINDOW *menuUI = newwin(menuHeight, menuWidth, menuStartY - 1, menuStartX);
    box(menuUI, 0, 0);

    for(int i = 0; i < items; i++)
        mvwprintw(menuUI, i + 1, 1, "%s", menus_items[i + 3]);

    wrefresh(menuUI);
    keypad(menuUI, TRUE);

    int choice = 0;

    while(1){
        for(int i = 0; i < items; i++){
            if(i == choice) wattron(menuUI, A_REVERSE);
            else wattroff(menuUI, A_REVERSE);
            mvwprintw(menuUI, i + 1, 1, "%-*s", menuWidth - 2, menus_items[i + 3]);
        }
        wrefresh(menuUI);

        int c = wgetch(menuUI);
        if(c == KEY_UP) choice = (choice - 1 + items) % items;
        else if(c == KEY_DOWN) choice = (choice + 1) % items;
        else if(c == '\n') break;
    }

    // return the selected index (0 = first menu item)
    return choice;
}
