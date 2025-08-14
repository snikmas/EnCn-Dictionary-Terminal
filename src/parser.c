#include "errors.h"
#include "parser.h"
#include "cJSON.h"
#include <stdio.h>

int parseResponse(char *response) {

    cJSON *json = cJSON_Parse(response);
    if (!json) {
        handleErrors(ERR_PARSER, "parseResponse");  // always handle
        return 1;
    }

    cJSON *word = cJSON_GetObjectItemCaseSensitive(json, "query");
    cJSON *translation = cJSON_GetObjectItemCaseSensitive(json, "translation");

    if (cJSON_IsString(word) && word->valuestring && cJSON_IsArray(translation)) {
        cJSON *firstItem = cJSON_GetArrayItem(translation, 0);
        if (cJSON_IsString(firstItem) && firstItem->valuestring) {
            printf("word: %s\n", word->valuestring);
            printf("translation: %s\n", firstItem->valuestring);
        } else {
            handleErrors(ERR_PARSER, "parseResponse");
        }
    } else {
        handleErrors(ERR_PARSER, "parseResponse");
    }



    cJSON_Delete(json);
    return 0;
}
