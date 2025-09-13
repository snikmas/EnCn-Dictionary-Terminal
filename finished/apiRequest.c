#include "headers/main.h"
#include "headers/ascii.h"
#include "headers/errors.h"
#include "headers/word.h"
#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userInput){
    
    size_t realSize = size * nmemb;
    struct data *tempData = (struct data *)userInput;
    char *ptr = realloc(tempData->response, tempData->size + realSize + 1);



    if(!tempData || !ptr) {
        handleErrors(ERR_OUT_OF_MEMORY, "write_data");
        return 0;
    }

    // new reallocated block
    tempData->response = ptr;

    // a new data to our buffer
    memcpy(&(tempData->response[tempData->size]), buffer, realSize);
    // recalculate the size
    tempData->size += realSize;
    tempData->response[tempData->size] = 0;

    return realSize;
}



void makeRequest(int option, Word *newWord, char *userInput){

    // if option == 0 -> EN->CN;

    char *url = malloc(512);
    struct data myData = {0};
    myData.response = NULL;  // Initialize to NULL to prevent undefined behavior
    myData.size = 0;
    
    // 2.setup curl
    
    if(curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK){
        free(url);
        free(userInput);
        free(myData.response);
        handleErrors(ERR_CURL_INIT_FAIL, "makeRequest");
    } 
        
    CURLcode res;
    CURL *curl = curl_easy_init();
    if(curl){

        buildUrl(url, userInput, option);
        
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &myData); // get data
        

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            free(url);
            free(myData.response);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            handleErrors(ERR_CURL_INIT_FAIL, "makeRequest");
        }

        parseResponse(myData.response, newWord, option);
        
        free(myData.response);
        free(url);
        curl_easy_cleanup(curl);
        curl_global_cleanup();

    } else {
        free(url);
        free(myData.response);
        handleErrors(ERR_CURL_INIT_FAIL, "makeRequest");
    }
        
}