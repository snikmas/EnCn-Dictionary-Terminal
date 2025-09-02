#ifndef WORD_H
#define WORD_H

#include <stdbool.h>

typedef struct Word {
  char *wordEn;
  char *wordCn;
  bool isFavorite;
} Word;

typedef struct NodeWord {
  struct NodeWord *next;
  Word *word;
} NodeWord;

// for hisory | favorite:
extern struct NodeWord *HEAD_HISTORY;
extern struct NodeWord *TAIL_HISTORY;

extern struct NodeWord *HEAD_FAV;
extern struct NodeWord *TAIL_FAV;


#endif