#include <ncurses.h>
#include <string.h>

#include "ascii.h"
#include "main.h"



int menuPage(){
    noecho();
    cbreak();
    curs_set(0);
    clear();
    
    erase();
    refresh();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // меню
    // int PROGRAM_WIDTH  = (xMax < 50) ? xMax - 2 : 50;
    int startX = (xMax - PROGRAM_WIDTH) / 2;

    // 1. Title Window
    WINDOW *titleWin = newwin(3, PROGRAM_WIDTH, 1, startX);
    if (!titleWin) return 4; // Exit if window creation fails
    
    // Draw box manually
    box(titleWin, 0, 0);
    
    mvwprintw(titleWin, 1, (PROGRAM_WIDTH - strlen(page_titles[0])) / 2, "%s", page_titles[0]);
    wrefresh(titleWin);

    // 2. Mascot Window
    int mascotWidth = 40; // ширина окна маскот
    int mascotHeight = LINES_MASCOT + 2;
    WINDOW *mascotWin = newwin(mascotHeight, mascotWidth, 5, (xMax - mascotWidth) / 2);
    if (!mascotWin) {
        delwin(titleWin);
        return 4;
    }
    
    // Draw box manually
    box(mascotWin, 0, 0);

    for(int i = 0; i < LINES_MASCOT; i++){
    int mx = (mascotWidth - strlen(mascots[0][i])) / 2; // центрируем строку в окне
    mvwprintw(mascotWin, i + 1, mx, "%s", mascots[0][i]);
    }
    wrefresh(mascotWin);


    // 3. Menu Window
    int menuItems = 5; // количество элементов меню 1
    int menuStartY = 5 + mascotHeight + 1;
    WINDOW *menuUI = newwin(menuItems + 2, PROGRAM_WIDTH, menuStartY, startX);
    if (!menuUI) {
        delwin(titleWin);
        delwin(mascotWin);
        return 4;
    }
    
    // Draw box manually
    box(menuUI, 0, 0);
    
    keypad(menuUI, TRUE);

    int choice = 0;
    while(1){
        for(int i = 0; i < menuItems; i++){
            if(i == choice) wattron(menuUI, A_REVERSE);
            else wattroff(menuUI, A_REVERSE);
            mvwprintw(menuUI, i + 1, 1, "%-*s", PROGRAM_WIDTH - 2, menus[0][i]);
        }
        wrefresh(menuUI);

        int c = wgetch(menuUI);
        if(c == KEY_UP) choice = (choice - 1 + menuItems) % menuItems;
        else if(c == KEY_DOWN) choice = (choice + 1) % menuItems;
        else if(c == '\n' || c == '\r' || c == ' ') break;
    }

    delwin(titleWin);
    delwin(mascotWin);
    delwin(menuUI);
    clear();
    refresh();

    return choice;
}

