#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "menu.h"

// later i will add
#include "translateMode.h"
#include "utils.h"
#include "main.h"
#include "errors.h"
#include "apiRequest.h"


int exitTheProgram() {return 0;};

int main(void){
  initscr();
  noecho();
  cbreak();
  curs_set(0);

  welcomePage();
  int choice = menuPage();
  
  switch(choice){
    case 0: translateMode(0); break; // EN -> CN
    case 1: translateMode(1); break; // CN -> EN
    case 2: viewSaved(); break;
    case 3: viewHistory(); break;
    case 4: endwin(); exit(0);       // exit
}


  return 0;
}