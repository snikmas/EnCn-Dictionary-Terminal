#include "apiRequest.h"

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



int makeRequest(int option, Word *newWord){

    // if option == 0;
    if (option == 0){
        printf("CH -> EN Mode\n");
    } else {
        printf("EN -> CN Mode\n");
    }

    char *url = malloc(512);

    char *userInput = malloc(99);
    if(!url || !userInput) {
        handleErrors(ERR_OUT_OF_MEMORY, "makeRequest");
        return 0;
    }

    
    printf("Input your word:\n>> ");
    if(fgets(userInput, 99, stdin) == NULL){
        handleErrors(ERR_OUT_OF_MEMORY, "makeRequest");
        return -1;
    }
    // remove trailing newline if any
    size_t len = strlen(userInput);
    if(len > 0 && userInput[len-1] == '\n') userInput[len-1] = '\0';
    
    

    struct data myData = {0};
    // 2.setup curl
    
    if(curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK){
        free(url);
        free(userInput);
        free(myData.response);
        handleErrors(ERR_CURL_INIT_FAIL, "makeRequest");
        return 0;

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
            handleErrors(ERR_CURL_INIT_FAIL, "makeRequest");
            return 0;
        }

        // parse: old word and new word
        parseResponse(myData.response, newWord, option);
        
        free(myData.response);
        curl_easy_cleanup(curl);
        curl_global_cleanup();

    } else {
        free(url);
        free(userInput);
        free(myData.response);
        handleErrors(ERR_CURL_INIT_FAIL, "makeRequest");
        return -1;
    }
        
    return 0;
}