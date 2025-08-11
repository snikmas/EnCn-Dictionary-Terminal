#include "makeRequest.h"
#include "apikeys.h"

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>
#include <openssl/sha.h>


char *response_data = NULL;
size_t response_size = 0;


int makeRequest(char *option){

  char *url = malloc(512);
  if(!url) return 5



  CURL *curl;
  CURLcode result;
  
  response_data = NULL;
  response_size = 0;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init(); 
  
  // later handle eng/chinese option
  if(curl){
    
    char *input = malloc(100);
    if(!input) return 5
    ;
    printf("Input your word:\n");
    
    scanf("%88s", input);
    
    // buffer to hold the final search url
    // HANDLE OPTIONs
    creatingLink(url, input, option);
    
  
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleMemory);
    curl_easy_setopt(curl, CURL_WRITEDATA, &response_data);
    
    
    result = curl_easy_perform(curl);
    if(result == CURLE_OK){
      handleResponse(response_data);
    } else {
      fprintf(stderr, "download problems: %s\n", curl_easy_strerror(result));
    }
    
    curl_easy_cleanup(curl);
  }
  
  curl_global_cleanup();
  
  return 0;
};

size_t handleMemory(char *ptrToData, size_t size, size_t numMembers, void *userInput){
  size_t realSize = size * numMembers;
  struct data *myData = (struct data*)userInput;
  
  char *ptr = realloc(myData->response, myData->size + realSize + 1);
  
  
  // idea: we can do funny stuff for errors
  if(!ptr){
    printf("Out of memory");
    return 4;
  }

  myData->response = ptr;
  memcpy(&mem->response[myData->size], data, realSize);
  myData->size += realSize;
  myData->response[myData->size] = 0;
  
  return realSize;
  
}

void creatingLink(char *url, char *userInput, char *option){
  
  // we need:
  // 1. url start yep
  // 2. q=input yep
  // 3. &langType=auto yep
  // 4. appKey=MYAPIKEY yep
  // 5. &dicts=ec OR ce yep
  // 6. &salt=UUID yep
  // 7. &sign=SIGN 
  // 8. &curtime=TIME_IN_SECONDS
  // 9. docType=json

  
  char *urlStart = "https://openapi.youdao.com/v2/dict";

  char *salt = malloc(sizeof(char) * 37);
  buildUUID(salt);
  
  // get currentTime
  time_t curtime = time(NULL)
  char curtime_str[20];
  snprintf(curtime_str, sizeof(curtime_str, "%ld", (long)curtime));


  // buidkds gin
  char *sign_string = malloc(sizeof(char) * 512);
  buildSign(sign_string, userInput, salt, currtime);
  
  char *urlRequest = malloc(512);
  if (!urlRequest) return 6;
  snprintf(urlRequest, sizeOf(urlRequest), 
    "%sq=%s&langType=auto&appKey=%s&dicts=%s&salt=%s&sign=%s&curTime=%s&docType=json", 
    url, userInput, API_KEY, dict, 
    salt, sign_string, currtime);
  
}



void buildUUID(char *salt){

  uuid_t binUuid;
  
  //generate uuid. we get not a str: a byte -> binary uuid
  uuid_generate_random(binUuid);
  
  // so we need to convert it to the str
  uuid_unparse_lower(binUuid, salt);
  
}

void buildSign(char *sign_string, char *userInput, char *uuid, char *curTime){

  
  char *sign = malloc(512);
  if (!sign) return 5;
  snprintf(sign, sizeof(sign_string), "%s%s%s%s%s", API_KEY, userInput, uuid, currtime, API_SECRET);

  sha256_string(sign, sign_string);

}


// generate ssl key for api
void sha256_string(const char *input, char outputBuffer[65]){
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;

  if(!SHA256_Init(&sha256)){
    printf("sha256_init failure");
    return 5;
  }
  
  
  if(!SHA256_Update(&sha256, input, strlen(input))) {
    printf("sha256_tting faulure");
    return 5;
  };
  if(!SHA256_Final(hash, &sha256)) {
    printf("sha256_tting faulure");
    return 5;
  };


  for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
    snprintf(outputBuffer + (i * 2), "%02x", hash[i]);
  }

  outputBuffer[64] = 0; 
}



void handleResponse(response_data){

  // just show the results 
  printf("%s", response_data);

}