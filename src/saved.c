#include "saved.h"

struct NodeWord *HEAD_SAVED = NULL;
struct NodeWord *TAIL_SAVED = NULL;


void viewSaved(){
  printf("SAVINGS LOG\n");

  if(HEAD_SAVED != NULL){

    int count = 1;
    for(struct NodeWord *i = HEAD_SAVED; i != NULL; i = i->next){
      printf("[%i] %s -> %s\n", count++, i->word->wordEn, i->word->wordCn);
    }
  } else {
    printf("No savings available.\n");
    printf("Tip: NO TIPS.\n");
    actions("onlyMenuBack", -1, NULL);
  }
  actions("savedAction", -1, NULL);
}

void addSavedWord(Word *newWord){
  

  struct NodeWord *newNode = malloc(sizeof(struct NodeWord));
  if (!newNode) handleErrors(ERR_OUT_OF_MEMORY, "addSavedWord");

  newNode->word = malloc(sizeof(Word));
  if(!newNode->word) {
    free(newNode);
    handleErrors(ERR_OUT_OF_MEMORY, "addSavedWord");
  }

  newNode->word = newWord;
  newNode->next = NULL;

  if(HEAD_SAVED == NULL) {
    HEAD_SAVED = newNode;
    TAIL_SAVED = newNode;
  } else {
    TAIL_SAVED->next = newNode;
    TAIL_SAVED = newNode;
  }

  printf("The word was added!\n");
}

void deleteSavedEntry(){
  printf("hi tom\n");
  printf("Input the number of the word that you would like to delete:\n>> ");
  int number = -1;
  while(1){
    if(scanf("%i", &number) != 1 || number > 9 || number < 0){
      printf("Invalid Input!\nTry again:\n>> ");
      while (getchar() != '\n');  
      number = -1; // reset choice
      continue;
    }

    break;
  }


  NodeWord *current = malloc(sizeof(NodeWord));
  
  current = HEAD_SAVED;
  if(number == 1){
    HEAD_SAVED = HEAD_SAVED->next;
    free(current->word);
    free(current);
    if(HEAD_SAVED == NULL) TAIL_SAVED = NULL;
  } else { 
    NodeWord *prev = malloc(sizeof(NodeWord));
    prev = NULL;
    for(int i = 1; i <= number && current != NULL; i++){
      prev = current;
      current = current->next;
    }

    if (current == NULL){
      printf("Position out of bounds!\n");
      viewSaved();
    } 
    prev->next = current->next;
    if(current == TAIL_SAVED){
      TAIL_SAVED = prev;
    }

    free(current->word);
    free(current);
  }

  printf("The word was successfully deleted!\n");
  viewSaved();
  
}

void deleteSaved(){
  printf("Are you sure you want to clear all savings?\n");
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
      
      if(choice == 0) viewSaved();
      else break;
    }

    struct NodeWord *delete = HEAD_SAVED;
    struct NodeWord *temp;
    while(delete != NULL){
      temp = delete->next;
      free(delete->word);
      free(delete);
      delete = temp;
    }
    HEAD_SAVED = NULL;
    TAIL_SAVED = HEAD_SAVED;

    printf("Savings was deleted.\n");
    viewSaved();
}

// operations: R - remove ALL
// operations: a - add a new word
// operations: r - remove one
void saved_operations(Word *newWord, char operation){
  switch(operation){
    case 'R':
      deleteSaved();
      break;
    case 'r':
      deleteSavedEntry();
      break;
    case 'a':
      addSavedWord(newWord);
      break;
  }
}