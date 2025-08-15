#include "translateMode.h"


void translateMode(int option){

  int stayInMode = 1;

  while (stayInMode){
    Word *newWord = malloc(sizeof(Word));
    if(!newWord){
      handleErrors(ERR_OUT_OF_MEMORY, "translationMode");
      return;
    }

    makeRequest(option, newWord);
    outputWord(newWord, option);

    int choice;
    if (scanf("%d", &choice) != 1) {
    printf("Invalid input. Please enter a number.\n");
    while (getchar() != '\n'); // flush bad input
    continue; // go back to start of while(stayInMode) loop
}

    switch(choice){
      case 1: continue;
      case 2: stayInMode = 0; break; // back to menu
      case 0: exit(0);
    }

    free(newWord);
  }

}