#include <stdio.h>
#include <stdlib.h>

// later i will add
#include "errors.h"
#include "utils.h"
#include "apiRequest.h"


int viewFavorites() { return 0;};
int viewHistory() { return 0;};
int help() {return 0;};
int exitTheProgram() {return 0;};


int main(void){

  int userPrompt;

  printf("\nNice to see you! This is Enlgish-Chinese Dictionary.\n\nMenu:\n");
  printf("1 → Translate EN → CH\n");
  printf("2 → Translate CN → EN\n");
  printf("3 → Favorites\n");
  printf("4 → History\n");
  printf("5 → Help\n");
  printf("0 → Exit\n");

  while(1){
    
    if(scanf("%i", &userPrompt) != 1){
      return 1;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // deafault 0: translate eng-ch; 1 -> chinese-eng
    switch(userPrompt){
      case 1: makeRequest(0); break;
      case 2: makeRequest(1); break;
      case 3: viewFavorites(); break;
      case 4: viewHistory(); break;
      case 5: help(); break;
      case 0: exitTheProgram(); return 0;
      default:
        printf("Wrong Input, User, Try again:\n");
    }
  }

  return 0;
}