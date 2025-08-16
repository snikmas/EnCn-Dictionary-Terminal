#include <stdio.h>
#include <stdlib.h>

// later i will add
#include "translateMode.h"
#include "utils.h"
#include "errors.h"
#include "apiRequest.h"


int viewFavorites() { return 0;};
int viewHistory() { return 0;};
int exitTheProgram() {return 0;};

int main(void){

  int continueProgram = 1;

  printf("\nNice to see you! This is Enlgish-Chinese Dictionary.\n\n");

  while(continueProgram){

    showMainMenu();
    // int choice = showMainMenu();

    // switch (choice) {
    //   case 1: translateMode(0); printf("en-cn mode\n");break; // en->cn
    //   case 2: translateMode(1); printf("cn-en mode\n"); break; // cn->en
    //   case 3: viewFavorites(); break;
    //   case 4: viewHistory(); break;
    //   case 0: exitTheProgram(); break;
    // }

    return 0;
  }
}