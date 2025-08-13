#include <stdio.h>
#include <stdlib.h>

#include "apikeys.h"
#include "apikeys.h"
#include "handleErrors.h"
#include "makeRequest.h"


int makeRequest(char *option);
int viewFavorites() { return 0;};
int viewHistory() { return 0;};
int help() {return 0;};
int exitTheProgram() {return 0;};
int handleErrors(int errorNumber) ;



int main(void){

  int input = -1;

  // can do timestemp and good evn good morn
  while(input != 0){
    printf("Nice to see you! This is Enlgish-Chinese Dictionary.\nMenu:");
    printf("1 - Translate English-Chinese\n");
    printf("2 - Translate Chinese-English\n");
    printf("3 - View Favorites\n");
    printf("4 - View History\n");
    printf("5 - Help\n");
    printf("0 - Exit The Program\n");

    scanf("%i", &input);

    switch(input){
      case 1: makeRequest("ec"); break;
      case 2: makeRequest("ce"); break;
      case 3: viewFavorites(); break;
      case 4: viewHistory(); break;
      case 5: help(); break;
      case 0: exitTheProgram(); break;
    }
  };

  return 0;
}