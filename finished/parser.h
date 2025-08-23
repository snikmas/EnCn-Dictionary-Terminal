#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "word.h"
#include "errors.h"
#include "cJSON.h"

void parseResponse(char *response, Word *newWord, int option);

#endif