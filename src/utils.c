#include "utils.h"

// actual definition (only once!)

void outputWord(Word *newWord, int option){

  history_operations(newWord, 'a');

  printf("────────────────────────────────\n");
  if(option == 0){ // default mode: en->chinese
    printf("Input: %s\n", newWord->wordEn);
    printf("Translation: %s\n", newWord->wordCn);
    // add pinuin
  } else { // 1: cn -> en
    printf("Input: %s\n", newWord->wordCn);
    printf("Translation: %s\n", newWord->wordEn);
  }
  printf("\n────────────────────────────────\n");


  actions("outputAction", option);
}


int showMainMenu(){
  int choice = -1;
  
  while (1) {
    printf("\nMenu:\n");
    printf("[1] Translate EN → CH\n");
    printf("[2] Translate CN → EN\n");
    printf("[3] Favorites\n");
    printf("[4] History\n");
    printf("[0] Exit\n");

    if (scanf("%i", &choice) != 1 || choice < 0 || choice > 4) {
      printf("Invalid Input! Please, try again.\n>> ");
      // clear input buffer
      while (getchar() != '\n');  
      choice = -1; // reset choice
      continue;
    }

    // clear leftover newline
    while (getchar() != '\n');

    switch (choice) {
      case 1: translateMode(0); printf("en-cn mode\n"); break; // en->cn
      case 2: translateMode(1); printf("cn-en mode\n"); break; // cn->en
      case 3: viewFavorites(); break;
      case 4: viewHistory(); break;
      case 0: exitTheProgram(); break;
    }
  }
}


void actions(char *entry, int option){
  
  int choice = -1;
  if(strcmp(entry, "outputAction") == 0){   
    // add: add to favorites
    printf("What would you like to do next?\n");
    printf("[1] Translate another word\n");
    printf("[2] Return to main menu\n");
    printf("[0] Exit program\n");
    
    while (1){
      if (scanf("%i", &choice) != 1 || choice < 0 || choice > 2 ){
        printf("Invalid Input.\nPlease, try again\n");
        while (getchar() != '\n');  
        choice = -1; // reset choice
        continue;
      }
      
      while (getchar() != '\n');
      
      switch(choice){
        case 1: translateMode(option); break;
        case 2: showMainMenu(); break;
        case 0: exit(0);
      }
    }
  } else if (strcmp(entry, "historyAction") == 0){
    printf("ACTIONS:\n");
    printf("[1] Delete an entry\n");
    printf("[2] Clear all history\n");
    printf("[0] Back to main menu\n");

    while (1){
      if (scanf("%i", &choice) != 1 || choice < 0 || choice > 2 ){
        printf("Invalid Input.\nPlease, try again\n");
        while (getchar() != '\n');  
        choice = -1; // reset choice
        continue;
      }
      
      while (getchar() != '\n');
      
      switch(choice){
        case 1: history_operations(NULL, 'r'); break;
        case 2: history_operations(NULL, 'R'); break;
        case 0: showMainMenu(); break;
      }
    }
  } else if(strcmp(entry, "onlyMenuBack") == 0){
    printf("ACTIONS:\n");
    printf("[0] Back to main menu\n");

    while (1){
      if (scanf("%i", &choice) != 1 || choice != 0){
        printf("Invalid Input.\nPlease, try again\n");
        while (getchar() != '\n');  
        choice = -1; // reset choice
        continue;
      }
      
      while (getchar() != '\n');
      
      switch(choice){
        case 0: showMainMenu(); break;
      }
    }
  }
}