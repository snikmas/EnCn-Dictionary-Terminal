#ifndef ALLDATA_H
#define ALLDATA_H

#include <stdio.h>
#include <stdlib.h>

int makeRequest(char *option);
int viewFavorites();
int viewStory();
int manageCollections();
int help();
int exitTheProgram();
int handleErrors(int errorNumber);


typedef struct {
  char wordEng[50];
  char wordChinese[50];
  char pinyin[50];
  bool isFavorite;
  char tags[50];
} Word;


#endif 