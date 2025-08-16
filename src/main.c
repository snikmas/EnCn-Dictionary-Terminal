#include <stdio.h>
#include <stdlib.h>

// later i will add
#include "translateMode.h"
#include "utils.h"
#include "errors.h"
#include "apiRequest.h"


int exitTheProgram() {return 0;};

int main(void){

  int continueProgram = 1;

  printf("\nNice to see you! This is Enlgish-Chinese Dictionary.\n\n");

  while(continueProgram){

    showMainMenu();

    return 0;
  }
}