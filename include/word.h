#ifndef WORD_H
#define WORD_H


#include <stdbool.h>

typedef struct {
    char *wordEn;
    char *wordCn;
    char *pinyin;
    bool isFavorite;
    char *tags;
} Word;




#endif 