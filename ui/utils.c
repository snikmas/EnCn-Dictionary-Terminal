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

    WINDOW *menuWin = newwin(menuHeight, menuWidth, menuStartY, menuStartX);
    box(menuWin, 0, 0);
    keypad(menuWin, TRUE);
    wrefresh(menuWin);

    int choice = 0;
    int ch;
    int saved = 0; // flag to track if word has been saved

    while (1) {
        // Draw menu
        for (int i = 0; i < num_items; i++) {
            if (i == choice) wattron(menuWin, A_REVERSE);
            else wattroff(menuWin, A_REVERSE);
            mvwprintw(menuWin, i + 1, 1, "%-*s", menuWidth - 2, action_items[i]);
        }
        wrefresh(menuWin);

        ch = wgetch(menuWin);

        // Handle saving word via '*'
        if (strcmp(entry, "outputAction") == 0 && ch == '*') {
            if (saved) {
                mvwprintw(menuWin, menuHeight + 1, 0, "The word has already been saved!");
            } else {
                addSavedWord(newWord);
                saved = 1;
                mvwprintw(menuWin, menuHeight + 1, 0, "[*] Word saved!");
                wrefresh(menuWin);
                napms(800);
                mvwprintw(menuWin, menuHeight + 1, 0, "                               "); // clear message
                wrefresh(menuWin);
            }
                continue; // stay in the menu
        }

        // Navigate menu
        if (ch == KEY_UP) choice = (choice - 1 + num_items) % num_items;
        else if (ch == KEY_DOWN) choice = (choice + 1) % num_items;
        else if (ch == '\n') {
            // Execute menu action
            if (strcmp(entry, "outputAction") == 0) {
                switch (choice) {
                    case 0: // Save word via Enter
                        if (!saved) {
                            addSavedWord(newWord);
                            saved = 1;
                            mvwprintw(menuWin, menuHeight - 1, 2, "[*] Word saved!");
                            wrefresh(menuWin);
                            napms(800);
                            mvwprintw(menuWin, menuHeight - 1, 2, "                               ");
                            wrefresh(menuWin);
                        }
                        break;
                    case 1: translateMode(option); break;
                    case 2: menuPage(); break; // back to main menu
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

            // Only break loop if user chose "Back" or "Exit"
            if ((strcmp(entry, "outputAction") == 0 && choice == 2) ||
                (strcmp(entry, "historyAction") == 0 && choice == 2) ||
                (strcmp(entry, "onlyMenuBack") == 0) ||
                (strcmp(entry, "savedAction") == 0 && choice == 2)) {
                break;
            }
        }
    }

    delwin(menuWin);
    refresh();
}
