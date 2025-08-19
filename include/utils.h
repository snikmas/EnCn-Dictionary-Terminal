#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ascii.h"
#include "saved.h"
#include "word.h"
#include "apiRequest.h"
#include "errors.h"
#include "translateMode.h"
#include "history.h"

int menuPage();
void welcomePage();
void actions(char *entry, int option, Word *newWord);
void viewHistory();
int exitTheProgram();
void translateMode(int option);
void outputWord(Word *newWord, int option);





#endif 