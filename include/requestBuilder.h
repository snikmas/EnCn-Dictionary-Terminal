#ifndef MAKEREQUEST_H
#define MAKEREQUEST_H

#include "word.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "apiRequest.h"
#include "parser.h"


char *buildUuid();
char *buildSha256(char *userInput, char *salt, char *curTime);
void buildUrl(char *url, char *userInput, int option);
char *buildTime();

#endif 
