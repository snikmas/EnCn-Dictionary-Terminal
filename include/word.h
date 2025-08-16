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

extern struct NodeWord *TAIL; // to get O(n)
extern struct NodeWord *HEAD;


void deleteHistory();
void deleteEntry();
void history_operations(Word *newWord, char operation);

#endif 