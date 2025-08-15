#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "word.h"
#include "apiRequest.h"
#include "errors.h"
#include "translateMode.h"

int showMainMenu();
int makeRequest(int option, Word *newWord);
int viewFavorites(); 
int viewHistory();
int help();
int exitTheProgram();
void outputWord(Word *newWord, int option);





#endif 