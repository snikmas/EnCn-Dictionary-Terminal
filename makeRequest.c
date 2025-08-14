#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>
#include <curl/curl.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#include "apikeys.h"
#include "makeRequest.h"

struct data {
    char *response;
    size_t size;
};


char *buildTime(){
    time_t curTime = time(0);
    char *curTime_str = malloc(20);

    // IS NOT GOOD CHECKING
    // if(!curTime_str) return curTime_str;
    snprintf(curTime_str, 20, "%lld", (long long)curTime);
    return curTime_str;
}


size_t write_data(void *buffer, size_t size, size_t nmemb, void *userInput){
    // total number of bytes in this chunk
    // the amount you'll append to your sotrage buffer
    size_t realSize = size * nmemb;
    struct data *tempData = (struct data *)userInput;

    // reallocs our currently struct for the response
    char *ptr = realloc(tempData->response, tempData->size + realSize + 1);
    if(!ptr) return 5; //out of memory

    // new reallocated block
    tempData->response = ptr;

    // a new data to our buffer
    memcpy(&(tempData->response[tempData->size]), buffer, realSize);
    // recalculate the size
    tempData->size += realSize;
    tempData->response[tempData->size] = 0;

    return realSize;
};

char *buildUuid(){
   uuid_t binuuid;
   uuid_generate(binuuid);

   char *uuid_str = malloc(37);
//    if(!uuid_str) return 5; IS NOT GOOD
   
   uuid_unparse(binuuid, uuid_str);

   return uuid_str;
}

char *buildSha256(char *userInput, char *salt, char *curTime){

    char *sign = malloc(512);
    snprintf(sign, 512, "%s%s%s%s%s", API_KEY, userInput, salt, curTime, API_SECRET);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len;

    // 1. create a message digest context
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if(mdctx == NULL){
        perror("EVP_MD_CTX_new");
        // return 6;
    }

    // 2. initialize the digest context for sha-256;
    if(EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1){
        perror("EVP_DigestInit_ex");
        // return 1;
    }
    
    // 3. hash the input
    if(EVP_DigestUpdate(mdctx, sign, strlen(sign)) != 1){
        perror("EVP_DigestUpdate");
        // return 6;
    }

    // 4. finalize the hash
    if(EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1){
        perror("EVP_DigestFinal_ex");
        // return 7;
    }

    // 5. free the context;
    EVP_MD_CTX_free(mdctx);

    // 6. convert to hex string
    char *sign_hash = malloc(hash_len * 2 + 1);

    for(unsigned int i = 0; i < hash_len; i++){
        sprintf(sign_hash + (i * 2), "%02x", hash[i]);
    }

    sign_hash[hash_len * 2] = '\0';

    printf("this is sha256: %s\n", sign_hash);

    return sign_hash;
}


int createUrl(char *url, char *userInput, int option){

    if(strlen(userInput) > 20) return 1;

    // for now: 1 word; <20 symbols
    
    // LINK FORMAT:
    // url?q=<word>&langType=auto&appKey=<myAppKey>&dicts=<option>&salt=<salt>&sign=<mySign>&signType=v3&curtime=<timestamp>&docType=json>
    char startUrl[] = "https://openapi.youdao.com/api";
    char *salt = buildUuid();
    char *curTime = buildTime();;
    char *sign = buildSha256(userInput, salt, curTime);
    char *languagePref = option == 0 ? "from=EN&to=zh-CHS" : "from=zh-CHS&to=en";


    // ========================================
    // ========================================
    CURL *curl = curl_easy_init(); // temporary curl handle just for escaping

    if(!curl){
        printf("no no no");
        return 5;
    }
    char *encodedInput = curl_easy_escape(curl, userInput, 0);
    char *encodedSign  = curl_easy_escape(curl, sign, 0);
    curl_easy_cleanup(curl);

    printf("start Url: %s\n", startUrl);
    printf("ECNOEDuserInp: %s\n", encodedInput);
    printf("key: %s\n", API_KEY);
    printf("option: %i\n", option);
    printf("salt: %s\n", salt);
    printf("ENCOEDEDsign: %s\n", encodedSign);
    printf("curtime: %s\n", curTime);
    
    snprintf(url, 512, 
        "%s?q=%s&%s&appKey=%s&salt=%s&sign=%s&signType=v3&curtime=%s", 
        startUrl, encodedInput, languagePref, API_KEY, salt, encodedSign, curTime);

    printf("full url string: %s\n", url);


    // cleanup
    free(salt);
    free(curTime);
    free(sign);
    curl_free(encodedInput);
    curl_free(encodedSign);

    return 0;
}



// ce or ec
int makeRequest(int option){

    char *url = malloc(512);
    if(!url) return 5;

    char *userInput = malloc(99);
    if(!userInput) return 1;

    
    printf("Input your word:\n>> ");
    fgets(userInput, 99, stdin);
    // remove trailing newline if any
    size_t len = strlen(userInput);
    if(len > 0 && userInput[len-1] == '\n') userInput[len-1] = '\0';
    
    

    struct data myData = {0};
    // 2.setup curl
    
    if(curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) return 5;

    CURLcode res;
    CURL *curl = curl_easy_init();
    if(curl){

        //3. write link
        createUrl(url, userInput, option);
        
        curl_easy_setopt(curl, CURLOPT_URL, url);
        // send data to this function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        // pass our chunk struct ti o here
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &myData); // get data
        
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) return 6;

        printf("\nAPI RSPONSE:\n%s\n", myData.response);
        free(myData.response);
        curl_easy_cleanup(curl);
        curl_global_cleanup();;

    } else {
        return 5;
    }
        

    return 0;

}