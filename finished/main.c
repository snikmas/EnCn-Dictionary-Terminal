#include "main.h"

int main(void){

  initscr();
  noecho();
  cbreak();
  curs_set(0);
  refresh();

  welcomePage(); // completed.

  int choice = menuPage();

  switch(choice){
    case 0: translateMode(0); break; // default: en->cn
    case 1: translateMode(1); break; // default: cn->en
    // case 2: viewSaved(); break; 
    // case 3: viewHistory(); break; 
    // case 4: endwin(); exit;
  }


  endwin();

  return 0;

}