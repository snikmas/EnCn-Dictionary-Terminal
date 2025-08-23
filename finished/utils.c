#include "ascii.h"
#include "word.h"
#include "main.h"

void actions(char *source, int mode, Word *newWord, int height) {
    noecho();
    cbreak();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    // Better positioning logic
    int actionsMenuY;
    if (height > 0 && height + 8 < yMax) {
        actionsMenuY = height + 2;
    } else {
        // Position at bottom of screen with some margin
        actionsMenuY = yMax - 8;
    }
    
    // Ensure it's within bounds
    if (actionsMenuY < 0) actionsMenuY = 0;
    if (actionsMenuY + 8 > yMax) actionsMenuY = yMax - 8;
    
    int actionsMenuW = PROGRAM_WIDTH;
    int startX = (xMax - PROGRAM_WIDTH) / 2;
    if (startX < 0) startX = 0;

    // Find which menu to show
    const char **cur_action_menu = NULL;
    int cur_len = 0;

    if (strcmp(source, "translateMode") == 0) {
        cur_action_menu = action_menus[0];
    } else if (strcmp(source, "historyAction") == 0) {
        cur_action_menu = action_menus[1];
    } else if (strcmp(source, "savedAction") == 0) {
        cur_action_menu = action_menus[2];
    } else if (strcmp(source, "onlyMenuBack") == 0) {
        cur_action_menu = action_menus[3];
    }

    // Count menu items
    if (cur_action_menu) {
        for (cur_len = 0; cur_action_menu[cur_len] != NULL; cur_len++);
    }

    // Ensure we have a valid menu
    if (cur_len == 0) {
        return;
    }

    WINDOW *actionsMenuWin = newwin(cur_len + 2, actionsMenuW, actionsMenuY, startX);
    int actionsMenuH = cur_len + 2;

    if (!actionsMenuWin) {
        return; // Window creation failed
    }

    // Draw box manually to ensure proper display
    box(actionsMenuWin, 0, 0);
    
    // Draw horizontal lines
    mvwhline(actionsMenuWin, 0, 1, ACS_HLINE, actionsMenuW-2);  // Top line
    mvwhline(actionsMenuWin, actionsMenuH-1, 1, ACS_HLINE, actionsMenuW-2); // Bottom line
    
    // Draw vertical lines
    mvwvline(actionsMenuWin, 1, 0, ACS_VLINE, actionsMenuH-2); // Left line
    mvwvline(actionsMenuWin, 1, actionsMenuW-1, ACS_VLINE, actionsMenuH-2); // Right line
    
    keypad(actionsMenuWin, TRUE);
    wrefresh(actionsMenuWin);
    
    // Ensure the window is visible
    touchwin(actionsMenuWin);
    wrefresh(actionsMenuWin);

    int choice = 0;
    int ch;
    int saved = 0; // flag to track if word has been saved

    while (1) {
        // Draw menu
        for (int i = 0; i < cur_len; i++) {
            if (i == choice)
                wattron(actionsMenuWin, A_REVERSE);
            else
                wattroff(actionsMenuWin, A_REVERSE);

            mvwprintw(actionsMenuWin, i + 1, 1, "%-*s",
                      PROGRAM_WIDTH - 2, cur_action_menu[i]);
        }
        wrefresh(actionsMenuWin);

        // Get input - simplified handling
        ch = wgetch(actionsMenuWin);

        // Handle quick-save via '*'
        if (strcmp(source, "translateMode") == 0 && ch == '*') {
            if (saved) {
                mvwprintw(actionsMenuWin, cur_len + 1, 2,
                          "The word has already been saved!");
            } else {
                addSavedWord(newWord);
                saved = 1;
                mvwprintw(actionsMenuWin, cur_len + 1, 2, "[*] Saved!");
            }
            wrefresh(actionsMenuWin);
            napms(800);
            mvwprintw(actionsMenuWin, cur_len + 1, 2,
                      "                                ");
            wrefresh(actionsMenuWin);
            continue;
        }

        // Navigate menu
        if (ch == KEY_UP) {
            choice = (choice - 1 + cur_len) % cur_len;
        } else if (ch == KEY_DOWN) {
            choice = (choice + 1) % cur_len;
        } else if (ch == '\n' || ch == '\r' || ch == ' ') {
            // ENTER, RETURN, or SPACE pressed → execute action
            if (strcmp(source, "translateMode") == 0) {
                switch (choice) {
                    case 0: // Save
                        if (!saved) {
                            addSavedWord(newWord);
                            saved = 1;
                            mvwprintw(actionsMenuWin, cur_len + 1, 2, "[*] Word saved!");
                            wrefresh(actionsMenuWin);
                            napms(800);
                            mvwprintw(actionsMenuWin, actionsMenuH, 2, "                                ");
                            wrefresh(actionsMenuWin);
                        }
                        // Continue showing the menu
                        break;
                    case 1: 
                        delwin(actionsMenuWin);
                        translateMode(mode); 
                        return; // Return after translation
                    case 2: 
                        delwin(actionsMenuWin);
                        menuPage(); 
                        return; // Return to main menu
                }
            } else if (strcmp(source, "historyAction") == 0) {
                switch (choice) {
                    case 0: 
                        // Delete an entry - stay in the same window
                        history_operations(NULL, 'r');
                        mvwprintw(actionsMenuWin, cur_len + 1, 2, "Entry deleted!");
                        wrefresh(actionsMenuWin);
                        napms(1000);
                        mvwprintw(actionsMenuWin, cur_len + 1, 2, "                                ");
                        wrefresh(actionsMenuWin);
                        // Refresh the view
                        delwin(actionsMenuWin);
                        viewHistory();
                        return;
                    case 1: 
                        // Clear all history - stay in the same window
                        history_operations(NULL, 'R');
                        mvwprintw(actionsMenuWin, cur_len + 1, 2, "All history cleared!");
                        wrefresh(actionsMenuWin);
                        napms(1000);
                        mvwprintw(actionsMenuWin, cur_len + 1, 2, "                                ");
                        wrefresh(actionsMenuWin);
                        // Refresh the view
                        delwin(actionsMenuWin);
                        viewHistory();
                        return;
                    case 2: 
                        delwin(actionsMenuWin);
                        menuPage(); 
                        return;
                }
            } else if (strcmp(source, "savedAction") == 0) {
                switch (choice) {
                    case 0: 
                        // Delete an entry - stay in the same window
                        saved_operations(NULL, 'r');
                        mvwprintw(actionsMenuWin, cur_len + 1, 2, "Entry deleted!");
                        wrefresh(actionsMenuWin);
                        napms(1000);
                        mvwprintw(actionsMenuWin, cur_len + 1, 2, "                                ");
                        wrefresh(actionsMenuWin);
                        // Refresh the view
                        delwin(actionsMenuWin);
                        viewSaved();
                        return;
                    case 1: 
                        // Clear all saved words - stay in the same window
                        saved_operations(NULL, 'R');
                        mvwprintw(actionsMenuWin, cur_len + 1, 2, "All saved words cleared!");
                        wrefresh(actionsMenuWin);
                        napms(1000);
                        mvwprintw(actionsMenuWin, cur_len + 1, 2, "                                ");
                        wrefresh(actionsMenuWin);
                        // Refresh the view
                        delwin(actionsMenuWin);
                        viewSaved();
                        return;
                    case 2: 
                        delwin(actionsMenuWin);
                        menuPage(); 
                        return;
                }
            } else if (strcmp(source, "onlyMenuBack") == 0) {
                delwin(actionsMenuWin);
                menuPage();
                return;
            }
        }
    }
    
    // Cleanup if we somehow exit the loop
    delwin(actionsMenuWin);
}
