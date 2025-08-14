#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    char *wordEng;
    char *wordChinese;
    char *pinyin;
    bool isFavorite;
    char *tags;
} Word;

extern Word words_list[100];

int makeRequest(int option);
int viewFavorites(); 
int viewHistory();
int help();
int exitTheProgram();





#endif 