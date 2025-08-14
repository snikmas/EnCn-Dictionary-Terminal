#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"
#include "cJSON.h"

int parseResponse(char *response);

#endif