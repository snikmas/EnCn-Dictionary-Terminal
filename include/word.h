#ifndef WORD_H
#define WORD_H


#include <stdbool.h>
#include <stddef.h>

typedef struct Word{
    char *wordEn;
    char *wordCn;
    char *pinyin;
    bool isFavorite;
    char *tags;
} Word;


typedef struct NodeWord{
    struct NodeWord *next;
    Word *word;
} NodeWord;

// for history
extern struct NodeWord *TAIL; // to get O(n)
extern struct NodeWord *HEAD;

// for favorites
extern struct NodeWord *TAIL_SAVED;
extern struct NodeWord *HEAD_SAVED;

void addWordHistory(Word *newWord);
void deleteHistory();
void deleteEntry();
void viewHistory();
void history_operations(Word *newWord, char operation);

#endif 