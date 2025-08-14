#ifndef MAKEREQUEST_H
#define MAKEREQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "apiRequest.h"
#include "utils.h"


int makeRequest(int option);
char *buildUuid();
char *buildSha256(char *userInput, char *salt, char *curTime);
int buildUrl(char *url, char *userInput, int option);
char *buildTime();

#endif 
