#include "ascii.h"
#include "word.h"
#include "main.h"

void actions(char *source, int mode, Word *newWord, int height){

  noecho();
  cbreak();
  curs_set(0);

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);
  int actionsMenuY = height + 2;
  int actionsMenuW = PROGRAM_WIDTH;
  
  // usually 3 items int he menu, so 3
  WINDOW *actionsMenuWin = newwin(3 + 2, actionsMenuW, actionsMenuY, (xMax - PROGRAM_WIDTH) / 2);

  box(actionsMenuWin, 0, 0);
  keypad(actionsMenuWin, TRUE);
  wrefresh(actionsMenuWin);

  int choice = 0;
  int ch; 
  int saved = 0; //falg to track if a word has saved;

  char *cur_action_menu;
  int cur_len; // 3
  if(strcmp(source, "translateMode")){
      cur_action_menu = action_menus[0];
      cur_len = sizeof(action_menus) / sizeof(cur_action_menu[0]);
    } else if (strcmp(source, "historyAction")) {
      cur_action_menu = action_menus[1];
      cur_len = sizeof(action_menus) / sizeof(cur_action_menu[0]);
    } else if(strcmp(source, "savedActoin")){
      cur_action_menu = action_menus[2];
      cur_len = sizeof(action_menus) / sizeof(cur_action_menu[0]);
    } else if (strcmp(source, "onlyMenuBack")){
      cur_action_menu = action_menus[3];
      cur_len = sizeof(action_menus) / sizeof(cur_action_menu[0]);
    }

  //  JUST OUPTUT ALL MENUS

  while(1){

    for(int i = 0; i < cur_len; i++){
      if(i == choice) wattron(actionsMenuWin, A_REVERSE);
      else wattroff(actionsMenuWin, A_REVERSE);
      mvwprintw(actionsMenuWin, i + 1, 1, "%-*s", PROGRAM_WIDTH - 2, cur_action_menu[i]);
    }

    wrefresh(actionsMenuWin);

    ch = wgetch(actionsMenuWin);

    // CASE MENU_1
    // handle saving word via *
    if(strcmp(source, "translateMode") == 0 && ch == '*'){
      if(saved){
        mvwprintw(actionsMenuWin, actionsMenuY + 1, PROGRAM_WIDTH / 2, "The Word has already saved!");
      } else {
        addSavedWord(newWord);
        saved = 1;
        mvwprintw(actionsMenuWin, actionsMenuY + 1, PROGRAM_WIDTH / 2, "Saved!");
        wrefresh(actionsMenuWin);
        napms(800);
        mvwprintw(actionsMenuWin, actionsMenuY + 1, PROGRAM_WIDTH / 2, "            "); //clear
        wrefresh(actionsMenuWin);
      }

      continue; // stay in the mnu
    }

    // NAVIGATE menu
    if(ch == KEY_UP) choice = (choice - 1 + cur_len % cur_len);
    else if (ch == KEY_DOWN) choice = (choice + 1) % cur_len;
    else if (ch == '\n') {
      if (strcmp(source, "outputAction") == 0) {
        switch (choice) {
          case 0: // Save word via Enter
            if (!saved) {
              addSavedWord(newWord);
              saved = 1;
              mvwprintw(actionsMenuWin, actionsMenuY - 1, 2, "[*] Word saved!");
              wrefresh(actionsMenuWin);
              napms(800);
              mvwprintw(actionsMenuWin, actionsMenuY - 1, 2, "                               ");
              wrefresh(actionsMenuWin);
            };
            break;
          case 1: translateMode(mode); break;
          case 2: menuPage(); break; // back to main menu
        }
      } else if (strcmp(source, "historyAction") == 0) {
        switch (choice) {
          case 0: history_operations(NULL, 'r'); break;
          case 1: history_operations(NULL, 'R'); break;
          case 2: menuPage(); break;
          }
      } else if (strcmp(source, "onlyMenuBack") == 0) {
        menuPage();
      } else if (strcmp(source, "savedAction") == 0) {
        switch (choice) {
          case 0: saved_operations(NULL, 'r'); break;
          case 1: saved_operations(NULL, 'R'); break;
          case 2: menuPage(); break;
        }
      }

      if ((strcmp(source, "outputAction") == 0 && choice == 2) ||
        (strcmp(source, "historyAction") == 0 && choice == 2) ||
        (strcmp(source, "onlyMenuBack") == 0) ||
        (strcmp(source, "savedAction") == 0 && choice == 2)) {
        break;
      }
    }
  }
  delwin(actionsMenuWin);
  refresh();

}