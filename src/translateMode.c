#include "translateMode.h"


void translateMode(int option){

  int stayInMode = 1;

  while (stayInMode){
    Word *newWord = malloc(sizeof(Word));
    if(!newWord){
      handleErrors(ERR_OUT_OF_MEMORY, "translationMode");
      return;
    }

    if (option == 0){
      printf("\nEN-> CN Mode\n");
    } else {
      printf("\nCN -> EN Mode\n");
    }


  char *userInput = malloc(21);
  if (!userInput) {
      handleErrors(ERR_OUT_OF_MEMORY, "translateMode");
  }

  size_t len = 0;
  do {
      printf("Input your word:\n>> ");
      if (!fgets(userInput, 21, stdin)) {
          printf("Invalid input. Try again.\n");
          continue;
      }

      // remove trailing newline
      len = strlen(userInput);
      if (len > 0 && userInput[len - 1] == '\n') userInput[len - 1] = '\0';

      len = strlen(userInput); // recalc length after trimming newline
      if (len == 0 || len > 21) {
          printf("Invalid input: max 20 characters. Try again.\n");
      }
  } while (len == 0 || len > 20);


    makeRequest(option, newWord, userInput); // done
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