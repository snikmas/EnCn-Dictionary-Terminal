#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>
#include <curl/curl.h>
#include <openssl/evp.h>

#include "apikeys.h"
// get word
// setup curl
// setup link

struct data {
    char *response;
    size_t size;
};


// receive data from the url->returns the number of bytes successfully handled
// buffer -> chunk of data that just received
// size -> size of each data element in bytes
// number of members
// user-provier data, our struct

char *buildTime(){
    time_t curTime = time(0);
    char *curTime_str = malloc(20);
    if(!curTime_str) return 5;
    snprintf(curTime_str, 20, "%lld", (long long)curTime);
    return curTime_str;
}


size_t write_data(void *buffer, size_t size, size_t nmemb, void *userInput){
    // total number of bytes in this chunk
    // the amount you'll append to your sotrage buffer
    size_t realSize = size * nmemb;
    struct data *tempData = (struct data *)userInput;

    // reallocs our currently struct for the response
    char *ptr = realloc(tempData->response, temp->size + realSize + 1);
    if(!ptr) return 5; //out of memory

    // new reallocated block
    temp->response = ptr;

    // a new data to our buffer
    memcpy(&(temp->response[temp->size]), buffer, realSize);
    // recalculate the size
    temp->size += realSize;
    temp->response[temp->size] = 0;

    return realSize;
};

char *buildUuid(){
   uuid_t binuuid;
   uuid_generate(binuuid);

   char *uuid_str = malloc(37);
   if(!uuid_str) return 5;
   
   uuid_unparse(binuuid, uuid_str);

   return uuid_str;
}

char *buildSha256(*userInput, *salt, *curTime){

    snprintf(&sign, signof(sign), "%s%s%s%s%s", API_ID, userInput, salt, curTime, API_SECRET);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len;

    // 1. create a message digest context
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if(mdctx == NULL){
        perror("EVP_MD_CTX_new");
        return 6;
    }

    // 2. initialize the digest context for sha-256;
    if(EVP_DigestInit_ex(mdctx, EVP_sHA256(), NULL) != 1){
        perrror("EVP_DigestInit_ex");
        return 1;
    }
    
    // 3. hash the input
    if(EVP_DigestUpdate(mdctx, userInput, strlen(userInput)) != 1){
        perror("EVP_DigestUpdate");
        return 6;
    }

    // 4. finalize the hash
    if(EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1){
        perror("EVP_DigestFinal_ex");
        return 7;
    }

    // 5. free the context;
    EVP_MD_CTX_free(mdctx);

    // 6. convert to hex string
    char sign[hash_len * 2 + 1];
    for(unsigned int i = 0; i < hash_len; i++){
        sprintf(sign + (i * 2), "%02x", hash[i]);
    }

    sign[hash_len * 2] = '\0';

    printf("this is sha256: %s\n", sign);

    return sign;
}


int createUrl(char *url, char *userInput, char *option){

    if(strlen(userInput) > 20) return 1;

    // for now: 1 word; <20 symbols
    
    // LINK FORMAT:
    // url?q=<word>&langType=auto&appKey=<myAppKey>&dicts=<option>&salt=<salt>&sign=<mySign>&signType=v3&curtime=<timestamp>&docType=json>
    char startUrl[] = "https://openapi.youdao.com/v2/dict";
    char *salt = buildUuid();
    char *curTime = buildTime();;
    char *sign = buildSha256(userInput, salt, curTime);

    snprintf(url, lengthTotal, 
        "%s?q=%s&langType=auto&appKey=%s&dicts=%s&salt=%s&sign=%s&signType=v3&curtime%s&docType=json", 
        startUrl, userInput, API_KEY, option, salt, sign, curTime);

    printf("full url string: %s\n");


    return 0;
}



// ce or ec
int makeRequest(char *option){

    char *url = malloc(512);
    if(!url) return 5;

    char *userInput = malloc(99);
    if(!userInput) return 1;

    
    printf("Input your word:\n>> ");
    if((scanf("%99s", userInput)) != 1){
        return 5;
    };
    

    struct data myData = {0};
    // 2.setup curl
    
    if(curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) return 5;

    CURLcode res;
    CURL *curl = curl_easy_init();
    if(curl){

        //3. write link
        createUrl(url, userInput, option);
        
        curl_easy_setopt(curl, CURLOPT_URL, "link");
        // send data to this function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        // pass our chunk struct ti o here
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &myData); // get data
        
        res = curl_easy_perform(curl);
        
        free(data.response);
        curl_easy_cleanup(curl);
        curl_global_cleanup();;

    } else {
        return 5;
    }
        


}