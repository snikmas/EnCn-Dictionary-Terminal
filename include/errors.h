#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int code;
    char *msg;
} Error;

#define ERR_OK 0
#define ERR_NOT_FOUND 1
#define ERR_CONN_FAIL 2
#define ERR_CURL_INIT_FAIL 3
#define ERR_OUT_OF_MEMORY 4  
#define ERR_SHA_EVP 5 
#define ERR_PARSER 6

// make extern if you want to use in multiple files
extern const Error error_list[];

void handleErrors(int errorCode, char *place);

#endif // ERRORS_H
