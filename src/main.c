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
  

  int continueProgram = 1;

  printf("\nNice to see you! This is Enlgish-Chinese Dictionary.\n\n");

  while(continueProgram){

    showMainMenu();

    return 0;
  }
}