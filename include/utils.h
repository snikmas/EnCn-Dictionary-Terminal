#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "saved.h"
#include "word.h"
#include "apiRequest.h"
#include "errors.h"
#include "translateMode.h"
#include "history.h"

void actions(char *entry, int option, Word *newWord);
int showMainMenu();
void viewHistory();
int exitTheProgram();
void outputWord(Word *newWord, int option);





#endif 