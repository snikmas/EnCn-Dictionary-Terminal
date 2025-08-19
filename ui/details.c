    // WINDOW *inputWin = newwin(3, menuWidth, menuStartY + menuHeight - 1, menuStartX);
    // box(inputWin, 0, ' ');
    // mvwprintw(inputWin,  1, 1, "Enter your command:");
    // wrefresh(inputWin);
    -> for unput


    // FULL MODE READY
//     #include <ncurses.h>
// #include <string.h>

// char *menus_items[] = {
//   "EN - CN Dictionary",
//   "Welcome, Hacker.\nTerminal Ready.",
//   "MENU",
//   "[1] Translate EN -> CN",
//   "[2] Translate CN -> EN",
//   "[3] Saved Translations",
//   "[4] History",
//   "[0] Exit",
// };

// int items = sizeof(menus_items) / sizeof(menus_items[0]) - 3;

// char *mascot[] = {
//         "  (\\_._/)",
//         "  ( o o )      Welcome, Hacker.",
//         "  /  V  \\      Terminal Ready.",
//         " /(  _  )\\",
//         "   ^^ ^^"
//     };

// int mascot_lines = sizeof(mascot) / sizeof(mascot[0]);



// int main() {
//     initscr();          // start ncurses
//     noecho();           // don’t echo input
//     cbreak();           // disable line buffering
//     curs_set(0);        // hide cursor


//     int xMax, yMax;
//     getmaxyx(stdscr, yMax, xMax);

//     WINDOW *menuTitle = newwin(5, 40, 0, 0);
//     box(menuTitle, 0, 0);

//     mvwprintw(menuTitle, 2, 10, menus_items[0]);
//     refresh();
//     wrefresh(menuTitle);

//     // good
//     int heightMenu, widthMenu;
//     getmaxyx(menuTitle, heightMenu, widthMenu);
//     WINDOW *mascotWin = newwin(mascot_lines + 2, xMax - 4, heightMenu, 2 );
  
//     for(int i = 0; i < mascot_lines; i++)
//       mvwprintw(mascotWin, i + 1, 1, "%s", mascot[i]);

//     wrefresh(mascotWin);

//     int heightMascot, widthMascot;
    
//     getmaxyx(mascotWin, heightMascot, widthMascot);
//     int menuHeight = items + 2;
//     int menuWidth = 40;
//     int menuStartY = heightMenu + heightMascot + 1;
//     int menuStartX = 0;

//     WINDOW *menuUI = newwin(menuHeight, menuWidth, menuStartY - 1, menuStartX);
//     box(menuUI, 0, 0);

//     for(int i = 3; i < 3 + items; i++){
//       mvwprintw(menuUI, i - 2, 1, "%s", menus_items[i]);
//     }
//     wrefresh(menuUI);
    
//     keypad(menuUI, TRUE);
//     int choice = 0;
    
//     while(1){
//       int menuWidth = 40;
//       for(int i = 0; i < items; i++){
//         if(i == choice) wattron(menuUI, A_REVERSE);
//         else wattroff(menuUI, A_REVERSE);

//         mvwprintw(menuUI, i + 1, 1, "%-*s", menuWidth - 2, menus_items[i + 3]);

//       }
//       wrefresh(menuUI);

//       int c = wgetch(menuUI);
//       if(c == KEY_UP){
//         choice = (choice - 1 + items) % items;
//       } else if(c == KEY_DOWN){
//         choice = (choice + 1) % items;
//       } else if(c == '\n'){
//         break;
//       }
//     }

//     clear();
//     getch();
// //     endwin();
// //     return 0;
// // }


// // =================

// #include <ncurses.h>
// #include <string.h>

// char *menus_items[] = {
//   "EN - CN Dictionary",
//   "EN -> CN Mode", 
//   "CN -> EN Mode"
// };

// int items = sizeof(menus_items) / sizeof(menus_items[0]);

// char *mascot[] = {
//         "  (\\_._/)",
//         "  ( ^ ^ )      Ready for input . . .",
//         "  /  V  \\",
//         " /(  _  )\\",
//         "   ^^ ^^"
//     };

// int mascot_lines = sizeof(mascot) / sizeof(mascot[0]);

// void draw_loading(WINDOW *loadingWin, int y, int x, int width, int percent) {
//     int fill = (percent * width) / 100;

//     // clear the line before drawing (prevents leftover chars)
//     mvwprintw(loadingWin, y, x, "[");
//     for (int i = 0; i < width; i++) {
//         waddch(loadingWin, (i < fill) ? '#' : '.');
//     }
//     waddch(loadingWin, ']');

//     wprintw(loadingWin, " %3d%%", percent);  // aligned percentage
//     wrefresh(loadingWin);
// }



// int main() {
//     initscr();          // start ncurses
//     noecho();           // don’t echo input
//     cbreak();           // disable line buffering
//     curs_set(0);        // hide cursor


//     int xMax, yMax;
//     getmaxyx(stdscr, yMax, xMax);

//     WINDOW *menuTitle = newwin(6, 40, 0, 0);
    
//     wrefresh(menuTitle);
//     mvwprintw(menuTitle, 2, 10, menus_items[0]);
//     mvwprintw(menuTitle, 3, 12, menus_items[1]);
//     box(menuTitle, 0, 0);
//     refresh();
//     wrefresh(menuTitle);

//     // good
//     int heightMenu, widthMenu;
//     getmaxyx(menuTitle, heightMenu, widthMenu);
//     WINDOW *mascotWin = newwin(mascot_lines + 2, xMax - 4, heightMenu, 2 );
  
//     for(int i = 0; i < mascot_lines; i++)
//       mvwprintw(mascotWin, i + 1, 1, "%s", mascot[i]);

//     wrefresh(mascotWin);

//     int heightMascot, widthMascot;
    
//     // // input hello and translations
//     getmaxyx(mascotWin, heightMascot, widthMascot);
//     int menuHeight = items + 5; 
//     int menuWidth = 40;
//     int menuStartY = heightMenu + heightMascot + 1;
//     int menuStartX = 0;

//     WINDOW *inputWin = newwin(menuHeight, menuWidth, menuStartY - 1, menuStartX);
//     // box(inputWin, 0, 0);

//     echo();
//     char *enterString = "Enter English Word: ";
//     mvwprintw(inputWin, 1, 2, "%s", enterString); // input from the user: symbols

//     curs_set(1);
//     char input[99];
//     wmove(inputWin, 1, strlen(enterString) + 2);
//     wgetnstr(inputWin, input, sizeof(input) - 1);
//     wrefresh(inputWin);

//     if(strlen(input) > 0 ){
//       mvwprintw(inputWin, 3, 2, "Processing translation...");
//       wrefresh(inputWin);
//       noecho();
//       curs_set(0);
//     }

//     // good. looks pretty not bad.
//     int loadingStartY = menuStartY + menuHeight - 5;
//     int loadingStartX = 0;
//     WINDOW *loadingWin = newwin(3, menuWidth, loadingStartY, loadingStartX);
//     wrefresh(loadingWin);
//     int barWidth = menuWidth - 10;
//     for(int i = 0; i <= 100; i += 10){
//       draw_loading(loadingWin, 1, 2, barWidth, i);
//       usleep(200000);
//     }

//     refresh();

//     int heightLoad, widthLoad;
//     getmaxyx(loadingWin, heightLoad, widthLoad); // 

//     WINDOW *resultWin = newwin(4, widthLoad, loadingStartY + heightLoad, 0);
//     box(resultWin, 0, 0);

//     int resultStartY, resultStartX;
//     getmaxyx(resultWin, resultStartY, resultStartX);
//     mvwprintw(resultWin, 1, 2, "Input: %s", input);
//     mvwprintw(resultWin, 2, 2, "Translation: resukt");
//     refresh();
//     wrefresh(resultWin);

//     // wait a little bit...
//     // output next commands



    
    
//     // clear();
//     getch();
//     endwin();
//     return 0;
// }
