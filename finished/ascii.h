#ifndef ASCII_H
#define ASCII_H

#define LINES_MASCOT 5
#define MAX_LEN_MASCOT 25
#define NUM_MASCOTS 1
#define PROGRAM_WIDTH 60

#include "word.h"
#include "main.h"
#include <stddef.h>

void addSavedWord(Word newWord);
void saved_operations(Word newWord, int mode);

extern const char **menus[3];
extern const char *action_menus[4];
extern const char *page_titles[3];
extern const char **mascots[NUM_MASCOTS];

struct data {
    char *response;
    size_t size;
};

void makeRequest(int option, Word *newWord, char *userInput);
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userInput);





#endif
