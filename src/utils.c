#include "utils.h"

// actual definition (only once!)
Word words_list[100];

void outputWord(Word *newWord, int option){
  printf("────────────────────────────────\n");
  if(option == 0){ // default mode: en->chinese
    printf("Input: %s\n", newWord->wordEn);
    printf("Translation: %s\n", newWord->wordCn);
    // add pinuin
  } else { // 1: cn -> en
    printf("Input: %s\n", newWord->wordCn);
    printf("Translation: %s\n", newWord->wordEn);
  }
  printf("────────────────────────────────\n");

  // add: add to favorites
  printf("What would you like to do next?\n");
  printf("[1] Translate another word\n");
  printf("[2] Return to main menu\n");
  printf("[0] Exit program\n");
  
  int choice = -1;
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
}


int showMainMenu(){
  int choice = -1;
  
  while (1) {
    printf("Menu:\n");
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

    return choice;
  }
}