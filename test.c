// #include <ncurses.h>
// #include <string.h>

// static char *menus_items[] = {
//     "Nice to see you! This is Enlgish-Chinese Dictionary.",
//     "[1] Translate EN → CH",
//     "[2] Translate CN → EN",
//     "[3] Saved",che
//     "[4] History",
//     "[0] Exit"
// };
// static int menu_items_count = sizeof(menus_items) / sizeof(menus_items[0]);

// int menuPage() {
//     int yMax, xMax;
//     getmaxyx(stdscr, yMax, xMax);
//     clear();
//     refresh();

//     int menuWidth = (xMax < 50) ? xMax - 4 : 50;
//     int menuHeight = menu_items_count + 4;

//     WINDOW *menuWin = newwin(menuHeight, menuWidth, (yMax - menuHeight) / 2, (xMax - menuWidth) / 2);
//     box(menuWin, 0, 0);
//     mvwprintw(menuWin, 1, 2, "%s", menus_items[0]);
//     for (int i = 1; i < menu_items_count; i++) {
//         mvwprintw(menuWin, i + 2, 2, "%s", menus_items[i]);
//     }
//     wrefresh(menuWin);

//     keypad(menuWin, TRUE);
//     int choice;
//     while (1) {
//         choice = wgetch(menuWin) - '0';
//         if (choice >= 0 && choice <= 4) {
//             break;
//         }
//     }

//     delwin(menuWin);
//     clear();
//     refresh();
//     return choice;
// }

// int main(void) {
//     initscr();
//     noecho();
//     cbreak();
//     curs_set(0);
//     keypad(stdscr, TRUE);
//     refresh();
//     menuPage();
//     endwin();
//     return 0;
// }