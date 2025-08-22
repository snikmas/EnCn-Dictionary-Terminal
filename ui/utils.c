#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "ascii.h"

void actions(char *entry, int option, Word *newWord) {
    noecho();
    cbreak();
    curs_set(0);

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    char *action_items[3];
    int num_items = 0;

    if (strcmp(entry, "outputAction") == 0) {
        action_items[0] = "[*] Save the word";
        action_items[1] = "[1] Translate another word";
        action_items[2] = "[2] Back to main menu";
        num_items = 3;
    } else if (strcmp(entry, "historyAction") == 0) {
        action_items[0] = "[1] Delete an entry";
        action_items[1] = "[2] Clear all history";
        action_items[2] = "[0] Back to main menu";
        num_items = 3;
    } else if (strcmp(entry, "onlyMenuBack") == 0) {
        action_items[0] = "[0] Back to main menu";
        num_items = 1;
    } else if (strcmp(entry, "savedAction") == 0) {
        action_items[0] = "[1] Delete an entry";
        action_items[1] = "[2] Clear all savings";
        action_items[2] = "[0] Back to main menu";
        num_items = 3;
    } else {
        return;
    }

    int menuHeight = num_items + 2;
    int menuWidth = 40;
    int menuStartY = (yMax - menuHeight) / 2;
    int menuStartX = (xMax - menuWidth) / 2;

    WINDOW *menuWin = newwin(menuHeight, menuWidth, menuStartY, 0);
    box(menuWin, 0, 0);
    keypad(menuWin, TRUE);
    wrefresh(menuWin);

    int choice = 0;
    int ch;

    while (1) {
        // Draw menu
        for (int i = 0; i < num_items; i++) {
            if (i == choice) wattron(menuWin, A_REVERSE);
            else wattroff(menuWin, A_REVERSE);
            mvwprintw(menuWin, i + 1, 1, "%-*s", menuWidth - 2, action_items[i]);
        }
        wrefresh(menuWin);

        ch = wgetch(menuWin);

        // Save word with '*'
        if (strcmp(entry, "outputAction") == 0 && ch == '*') {
            if(option == -2){
              mvprintw(menuWin, menuHeight - 1, 2, "The word has already saved");
              wrefresh(menuWin);
              napms(800);
              actions(entry, -2, newWord);
            }
            addSavedWord(newWord);
            mvwprintw(menuWin, menuHeight - 1, 2, "[*] Word saved!");
            wrefresh(menuWin);
            napms(800);
            mvwprintw(menuWin, menuHeight - 1, 2, "                     "); // clear message
            wrefresh(menuWin);
            actions(entry, -2, newWord);
            break;
        }

        if (ch == KEY_UP) choice = (choice - 1 + num_items) % num_items;
        else if (ch == KEY_DOWN) choice = (choice + 1) % num_items;
        else if (ch == '\n') {
            if (strcmp(entry, "outputAction") == 0) {
                switch (choice) {
                    case 0: addSavedWord(newWord); break;  // Save the word
                    case 1: translateMode(option); break;
                    case 2: menuPage(); break;
                }
            } else if (strcmp(entry, "historyAction") == 0) {
                switch (choice) {
                    case 0: history_operations(NULL, 'r'); break;
                    case 1: history_operations(NULL, 'R'); break;
                    case 2: menuPage(); break;
                }
            } else if (strcmp(entry, "onlyMenuBack") == 0) {
                menuPage();
            } else if (strcmp(entry, "savedAction") == 0) {
                switch (choice) {
                    case 0: saved_operations(NULL, 'r'); break;
                    case 1: saved_operations(NULL, 'R'); break;
                    case 2: menuPage(); break;
                }
            }
            break;
        }
    }

    delwin(menuWin);
    refresh();
}
