#include "handleErrors.h"

int handleErrors(int errorNumber){

  get_error_msg(errorNumber);

  return errorNumber;

}


static const Error error_list[] = {
  { ERR_OK, "No error"},
  { ERR_NOT_FOUND, "Item not found"},
  { ERR_CONN_FAIL, "Connection failed"},
  { ERR_CURL_INIT_FAIL, "Curl Init failed"}
};

const int error_list_size = sizeof(error_list) / sizeof(Error);

const char *get_error_msg(int code){
  for(int i = 0; i < error_list_size; i++){
    if(error_list[i].code == code){
      return error_list[i].msg;
    }
  }

  return "Unknown error";
}