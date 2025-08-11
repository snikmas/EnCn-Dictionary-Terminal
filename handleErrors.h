#ifndef HANDLEERRORS_H
#define HANDLEERRORS_H

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

const char *get_error_msg(int code);
int handleErrors(int errorNumber);


#endif // ERROR_H