#ifndef MAKEREQUEST_H
#define MAKEREQUEST_H

#include <stdio.h>
#include <stdlib.h>



struct data {
  char *response;
  size_t size;
};

int makeRequest(char *option);
int handleResponse(char *response_data);
int sha256_string(const char *input, char outputBuffer[65]);
int buildUUID(char *salt);
int buildSign(char *sign_string, char *userInput, char *uuid, char *curTime);
int creatingLink(char *url, char *userInput, char *option);
size_t handleMemory(char *ptrToData, size_t size, size_t numMembers, void *userInput);

#endif 