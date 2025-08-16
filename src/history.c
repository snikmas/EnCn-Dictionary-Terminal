#include "history.h"


struct NodeWord *HEAD = NULL;
struct NodeWord *TAIL = NULL;

void addWordHistory(Word *newWord){

  struct NodeWord *newNode = malloc(sizeof(struct NodeWord));
  if (!newNode) handleErrors(ERR_OUT_OF_MEMORY, "addWordHistory");

  newNode->word = malloc(sizeof(Word));
  if(!newNode->word) handleErrors(ERR_OUT_OF_MEMORY, "addWordHistory");

  newNode->word = newWord;
  newNode->next = NULL;

  if(HEAD == NULL) {
    HEAD = newNode;
    TAIL = newNode;
  } else {
    TAIL->next = newNode;
    TAIL = newNode;
  }

}

void viewHistory(){
  printf("HISTORY LOG\n");
  
  if (HEAD != NULL){

    int count = 1;
    for(struct NodeWord *i = HEAD; i != NULL; i = i->next){
      printf("[%i] %s -> %s\n", count++, i->word->wordEn, i->word->wordCn);
    }
  } else {
    printf("No history available.\n");
    printf("Tip: Every translation is automatically saved here.\n");
    actions("onlyMenuBack", -1);
  }
  actions("historyAction", -1);

}

void deleteHistory(){
  printf("Are you sure you want to clear all history?\n");
  printf("[1] Yes\n");
  printf("[0] No\n");
  
  int choice = -1;

  while (1){
    if (scanf("%i", &choice) != 1 || choice > 1 || choice < 0 ){
        printf("Invalid Input.\nPlease, try again\n");
        while (getchar() != '\n');  
        choice = -1; // reset choice
        continue;
      }
      
      while (getchar() != '\n');
      
      if(choice == 0) viewHistory();
      else break;
    }

    struct NodeWord *delete = HEAD;
    struct NodeWord *temp;
    while(delete != NULL){
      temp = delete->next;
      free(delete->word);
      free(delete);
      delete = temp;
    }
    HEAD = NULL;
    TAIL = HEAD;

    printf("History was deleted.\n");
    viewHistory();
}

void deleteEntry(){
  printf("hi bob");
  showMainMenu();
}




// operations:
// R - remove all
// a - add a new word
// r - remove one word
void history_operations(Word *newWord, char operation){

  switch(operation){
    case 'a':
      addWordHistory(newWord);
      break;
    case 'R':
      deleteHistory();
      break;
    case 'r':
      deleteEntry();
      break;
  }
}
