#include "headers/ascii.h"
#include "headers/main.h"

char *buildTime(){
    time_t curTime = time(0);
    char *curTime_str = malloc(20);
    if (!curTime_str){
        handleErrors(ERR_OUT_OF_MEMORY, "buildTime");
        return NULL;
    }

    snprintf(curTime_str, 20, "%lld", (long long)curTime);
    return curTime_str;
}


char *buildUuid(){
   uuid_t binuuid;
   uuid_generate(binuuid);

   char *uuid_str = malloc(37);
   if(!uuid_str){
    handleErrors(ERR_OUT_OF_MEMORY, "buildUuid");
    return NULL;
   }
    //check error

   uuid_unparse(binuuid, uuid_str);

   return uuid_str;
}

char *buildSha256(char *userInput, char *salt, char *curTime){

    char *sign = malloc(512);
    if(!sign){
        handleErrors(ERR_OUT_OF_MEMORY, "buildSha256");
        return NULL;

    }


    snprintf(sign, 512, "%s%s%s%s%s", API_KEY, userInput, salt, curTime, API_SECRET);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len;

    // 1. create a message digest context
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if(mdctx == NULL){
        free(sign);
        perror("EVP_MD_CTX_new");
        handleErrors(ERR_SHA_EVP, "buildSha256");
        return NULL;

    }
    
    // 2. initialize the digest context for sha-256;
    if(EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1){
        free(sign);
        perror("EVP_DigestInit_ex");
        handleErrors(ERR_SHA_EVP, "buildSha256");
        return NULL;

    }
    
    // 3. hash the input
    if(EVP_DigestUpdate(mdctx, sign, strlen(sign)) != 1){
        free(sign);
        perror("EVP_DigestUpdate");
        handleErrors(ERR_SHA_EVP, "buildSha256");
        return NULL;

    }
    
    // 4. finalize the hash
    if(EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1){
        free(sign);
        perror("EVP_DigestFinal_ex");
        handleErrors(ERR_SHA_EVP, "buildSha256");
        return NULL;

    }
    
    // 5. free the context;
    EVP_MD_CTX_free(mdctx);
    
    // 6. convert to hex string
    char *sign_hash = malloc(hash_len * 2 + 1);
    if(!sign_hash){
        free(sign);
        handleErrors(ERR_SHA_EVP, "buildSha256");
        return NULL;

    }

    for(unsigned int i = 0; i < hash_len; i++){
        sprintf(sign_hash + (i * 2), "%02x", hash[i]);
    }

    sign_hash[hash_len * 2] = '\0';

    return sign_hash;
}



void buildUrl(char *url, char *userInput, int option){
    
    char startUrl[] = "https://openapi.youdao.com/api";
    char *salt = buildUuid();
    char *curTime = buildTime();;
    char *sign = buildSha256(userInput, salt, curTime);
    char *languagePref = option == 0 ? "from=EN&to=zh-CHS" : "from=zh-CHS&to=en";
    if(!salt || !curTime || !sign || !languagePref){
        handleErrors(ERR_OUT_OF_MEMORY, "buildUrl");
    }


    CURL *curl = curl_easy_init();
    if(!curl){
        free(salt);
        free(curTime);
        free(sign);
        handleErrors(ERR_CURL_INIT_FAIL, "buildUrl");
    }

    char *encodedInput = curl_easy_escape(curl, userInput, 0);
    if(!encodedInput){
        free(salt);
        free(sign);
        free(curTime);
        curl_easy_cleanup(curl);
        handleErrors(ERR_OUT_OF_MEMORY, "buildUrl");
    }
    
    snprintf(url, 512, 
        "%s?q=%s&%s&appKey=%s&salt=%s&sign=%s&signType=v3&curtime=%s", 
        startUrl, encodedInput, languagePref, API_KEY, salt, sign, curTime);
        
    
    
    free(salt);
    free(curTime);
    curl_free(encodedInput);
    curl_easy_cleanup(curl);
}


