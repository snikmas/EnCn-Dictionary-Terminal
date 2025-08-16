#ifndef SAVED_H
#define SAVED_H

#include "translateMode.h"
#include "utils.h"
#include "word.h"


void deleteSaved();
void saved_operations(Word *newWord, char operation);
void deleteSavedEntry();
void addSavedWord(Word *newWord);
void viewSaved();

#endif