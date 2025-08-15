#include "errors.h"
#include "parser.h"
#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parseResponse(char *response, Word *newWord, int option) {

    cJSON *json = cJSON_Parse(response);
    if (!json) {
        handleErrors(ERR_PARSER, "parseResponse");
        return 1;
    }


    cJSON *wordJson = cJSON_GetObjectItemCaseSensitive(json, "query");
    cJSON *translationArrJson = cJSON_GetObjectItemCaseSensitive(json, "translation");

    if (cJSON_IsString(wordJson) && cJSON_IsArray(translationArrJson)) {

        // it returns an array of translations: choose the 1st one
        cJSON *translationJson = cJSON_GetArrayItem(translationArrJson, 0);

        if (cJSON_IsString(translationJson)) {
            if(option == 0){
                // default: en -> chinese
                newWord->wordEn = strdup(wordJson->valuestring);
                newWord->wordCn = strdup(translationJson->valuestring);
            }
        } else {
            handleErrors(ERR_PARSER, "parseResponse");
        }

    } else {
        handleErrors(ERR_PARSER, "parseResponse");
    }

    cJSON_Delete(json);
    return 0;
}
