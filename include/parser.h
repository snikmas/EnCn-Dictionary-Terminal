#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "word.h"
#include "utils.h"
#include "errors.h"
#include "cJSON.h"
#include "requestBuilder.h"

int parseResponse(char *response, Word *newWord, int option);

#endif