#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

// later i will add
#include "ascii.h"
#include "utils.h"
#include "translateMode.h"
#include "main.h"
#include "errors.h"
#include "apiRequest.h"


int exitTheProgram() {return 0;};

int main(void){
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  refresh();

  welcomePage();
  // refresh();
  int choice = menuPage();
  
  switch(choice){
    case 0: translateMode(0); break; // EN -> CN
    case 1: translateMode(1); break; // CN -> EN
    case 2: viewSaved(); break;
    case 3: viewHistory(); break;
    case 4: endwin(); exit(0);       // exit
}

  endwin();

  return 0;
}