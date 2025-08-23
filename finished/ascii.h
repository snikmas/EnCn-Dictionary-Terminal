#ifndef ASCII_H
#define ASCII_H

#define LINES_MASCOT 5
#define MAX_LEN_MASCOT 25
#define NUM_MASCOTS 1
#define PROGRAM_WIDTH 60

#include "main.h"
#include "word.h"
#include <stddef.h>

extern const char *const *menus[3];
extern const char *const *action_menus[4];
extern const char *const page_titles[3];
extern const char *const *mascots[NUM_MASCOTS];

struct data {
    char *response;
    size_t size;
};

void makeRequest(int option, Word *newWord, char *userInput);
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userInput);





#endif
