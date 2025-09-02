#include "errors.h"

#include "main.h"
#include "ascii.h"
#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parseResponse(char *response, Word *newWord, int option) {
    
    // response from the server
    // mvprintw(1, 0, "DEBUG: response = %s\n", response);

    if(!response || strlen(response) == 0) {
        handleErrors(ERR_PARSER, "parseResponse response is empty");
        return;
    };

    cJSON *json = cJSON_Parse(response);
    if (!json) {
        handleErrors(ERR_PARSER, "parseResponse jso0");
        return;
    }

    cJSON *wordJson = cJSON_GetObjectItemCaseSensitive(json, "query");
    cJSON *translationArrJson = cJSON_GetObjectItemCaseSensitive(json, "translation");
    
    if (cJSON_IsString(wordJson) && cJSON_IsArray(translationArrJson) && cJSON_GetArraySize(translationArrJson) > 0) {

        cJSON *translationJson = cJSON_GetArrayItem(translationArrJson, 0);

        if (cJSON_IsString(translationJson)) {
            if(option == 0){ // default: en->cn
                newWord->wordEn = strdup(wordJson->valuestring);
                newWord->wordCn = strdup(translationJson->valuestring);
            } else { // option == 1 CN->en
                newWord->wordCn = strdup(wordJson->valuestring);
                newWord->wordEn = strdup(translationJson->valuestring);
            }
        } else {
            handleErrors(ERR_PARSER, "parseResponse JSOOOOOOOOn1");
        }

    } else {
        handleErrors(ERR_PARSER, "parseResponse JAOOOOOOOON2");
    }

    cJSON_Delete(json);
}
