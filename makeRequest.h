#ifndef MAKEREQUEST_H
#define MAKEREQUEST_H

#include <stdio.h>
#include <stdlib.h>


struct data {
  char *response;
  size_t size;
};

int makeRequest(char *option);

void handleResponse(char *response_data);

void sha256_string(const char *input, char outputBuffer[65]);
void buildUUID(char *salt);

void buildSign(char *sign_string, char *userInput, char *uuid, char *curTime);

void creatingLink(char *url, char *userInput, char *option);

size_t handleMemory(char *ptrToData, size_t size, size_t numMembers, void *userInput);

#endif 