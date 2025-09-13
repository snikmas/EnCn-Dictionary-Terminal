#include "headers/main.h"
#include "headers/errors.h"

const Error error_list[] = {
  { ERR_OK, "No error"},
  { ERR_NOT_FOUND, "Item not found"},
  { ERR_CONN_FAIL, "Connection failed"},
  { ERR_CURL_INIT_FAIL, "Curl Init failed"},
  { ERR_OUT_OF_MEMORY, "Out of memory"},
  { ERR_SHA_EVP, "EVP function failed"},
  { ERR_PARSER, "Parser Failed"}
};

void handleErrors(int errorCode, char *place){
  if (errorCode == ERR_OK) return;

  
  printf("Error: %s in the %s\nFinishing the program...\n", error_list[errorCode].msg, place);
  exit(1);
}
  