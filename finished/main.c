#include "main.h"

int main(void){

  initscr();
  noecho();
  cbreak();
  curs_set(0);
  refresh();

  // during this debugging, no need
  // welcomePage(); // completed.

  
  int running = 1;
  while(running){

    flushinp();
    int choice = menuPage();
    
    switch(choice){
      case 0: translateMode(0); break; // default: en->cn
      case 1: translateMode(1); break; // default: cn->en
      case 2: viewSaved(); break; 
      case 3: viewHistory(); break; 
      case 4: running = 0; break; // Exit program
      default: break;
    }
    clear();
    refresh();
    
  }

  endwin();

  return 0;

}