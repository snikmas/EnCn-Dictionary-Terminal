#include "word.h"
#include "ascii.h"
#include "main.h"

void history_operations(Word *newWord, char operation){
  if (operation == 'r') {
    // Delete a history entry (remove first entry for now)
    if (HEAD_HISTORY != NULL) {
      struct NodeWord *temp = HEAD_HISTORY;
      HEAD_HISTORY = HEAD_HISTORY->next;
      
      if (temp->word) {
        if (temp->word->wordEn) free(temp->word->wordEn);
        if (temp->word->wordCn) free(temp->word->wordCn);
        free(temp->word);
      }
      free(temp);
      
      if (HEAD_HISTORY == NULL) {
        TAIL_HISTORY = NULL;
      }
    }
  } else if (operation == 'R') {
    // Clear all history
    struct NodeWord *current = HEAD_HISTORY;
    while (current != NULL) {
      struct NodeWord *temp = current;
      current = current->next;
      
      if (temp->word) {
        if (temp->word->wordEn) free(temp->word->wordEn);
        if (temp->word->wordCn) free(temp->word->wordCn);
        free(temp->word);
      }
      free(temp);
    }
    HEAD_HISTORY = NULL;
    TAIL_HISTORY = NULL;
  }
}