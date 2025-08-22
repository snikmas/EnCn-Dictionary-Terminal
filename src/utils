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


  actions("outputAction", option, newWord);
  actions("isToSave", -1, newWord);
}


void actions(char *entry, int option, Word *newWord){
  
  int choice = -1;
  char ch;
  if(strcmp(entry, "outputAction") == 0){   
    // add: add to favorites
    printf("[*] To save the word\n\n");
    printf("What would you like to do next?\n");
    printf("[1] Translate another word\n");
    printf("[2] Return to main menu\n");
    printf("[0] Exit program\n");


    
    while (1){
      ch = getchar();
      
      if(ch == '*'){
        choice = 42;
      } else if(ch >= '0' && ch <='3'){
        choice = ch - '0';
      } else {
        choice = -1;
      }

      if (choice != 42 && (choice < 0 || choice > 2 )){
        printf("Invalid Input.\nPlease, try again\n");
        while (getchar() != '\n');  
        choice = -1; // reset choice
        continue;
      }
      
      while (getchar() != '\n');

      
      switch(choice){
        case 42: 
          addSavedWord(newWord);
          choice = -1;
          continue;
        case 1: translateMode(option); break;
        case 2: menuPage(); break;
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
        case 0: menuPage(); break;
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
        case 0: menuPage(); break;
      }
    }
  } else if (strcmp(entry, "savedAction") == 0){
    printf("ACTIONS:\n");
    printf("[1] Delete an entry\n");
    printf("[2] Clear all savings\n");
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
        case 1: saved_operations(NULL, 'r'); break;
        case 2: saved_operations(NULL, 'R'); break;
        case 0: menuPage(); break;
      }
    }
  }
}