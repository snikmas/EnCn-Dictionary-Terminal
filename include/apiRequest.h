#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>
#include <curl/curl.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#include "config.h"
#include "errors.h"
#include "requestBuilder.h"

struct data {
    char *response;
    size_t size;
};

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userInput);


#endif