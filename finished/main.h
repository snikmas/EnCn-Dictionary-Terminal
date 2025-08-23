#ifndef MAIN_H
#define MAIN_H

// own
#include "ascii.h"
#include "config.h"
#include "errors.h"
#include "word.h"
#include "parser.h"

// common
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <ctype.h>
#include <stddef.h>

// apiReq
#include <curl/curl.h>
#include <uuid/uuid.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

// parser
#include "cJSON.h"

// Function declarations
void buildUrl(char *url, char *userInput, int option);
void makeRequest(int option, Word *newWord, char *userInput);
void translateMode(int mode);
int menuPage(void);
void welcomePage(void);
void addSavedWord(Word *newWord);
void addToHistory(Word *newWord);
void saved_operations(Word *newWord, char operation);
void actions(char *source, int mode, Word *newWord, int height);
void history_operations(Word *newWord, char operation);
void viewSaved(void);
void viewHistory(void);

#endif