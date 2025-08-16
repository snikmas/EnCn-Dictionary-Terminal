#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "word.h"
#include "utils.h"
#include "errors.h"


void deleteHistory();
void deleteEntry();
void viewHistory();
void addWordHistory(Word *newWord);
void history_operations(Word *newWord, char operation);
// extern Word words_list[100];



#endif 