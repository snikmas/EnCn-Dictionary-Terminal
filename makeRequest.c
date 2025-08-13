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

size_t handleMemory(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realSize = size * nmemb;
    struct data *mem = (struct data *)userdata;

    char *temp = realloc(mem->response, mem->size + realSize + 1);
    if (!temp) {
        fprintf(stderr, "Out of memory\n");
        return 0;
    }
    mem->response = temp;

    memcpy(&(mem->response[mem->size]), ptr, realSize);
    mem->size += realSize;
    mem->response[mem->size] = 0;

    return realSize;
}

int buildUUID(char *salt) {
    uuid_t binUuid;
    uuid_generate_random(binUuid);
    uuid_unparse_lower(binUuid, salt);
    return 0;
}

int sha256_string(const char *input, char output[65]) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) return 1;

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return 2;
    }

    if (EVP_DigestUpdate(mdctx, input, strlen(input)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return 3;
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    if (EVP_DigestFinal_ex(mdctx, hash, &lengthOfHash) != 1) {
        EVP_MD_CTX_free(mdctx);
        return 4;
    }

    EVP_MD_CTX_free(mdctx);

    for (unsigned int i = 0; i < lengthOfHash; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = 0;
    return 0;
}

int buildSign(char *sign_string, const char *userInput, const char *salt, const char *curtime) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s%s%s%s%s", API_KEY, userInput, salt, curtime, API_SECRET);
    return sha256_string(buffer, sign_string);
}

int buildPostFields(char *postfields, size_t size, const char *encodedInput, const char *option, const char *salt, const char *originalInput) {
    time_t curtime = time(NULL);
    char curtime_str[20];
    snprintf(curtime_str, sizeof(curtime_str), "%ld", (long)curtime);

    char sign_string[65];
    if (buildSign(sign_string, originalInput, salt, curtime_str) != 0) {
        fprintf(stderr, "Failed to build sign\n");
        return 1;
    }

    printf("API_KEY: %s\n", API_KEY);
printf("API_SECRET: %s\n", API_SECRET);
printf("User Input: %s\n", originalInput);
printf("Salt: %s\n", salt);
printf("Curtime: %s\n", curtime_str);
printf("Sign string: %s\n", sign_string);
printf("Postfields: %s\n", postfields);


    snprintf(postfields, size,
        "q=%s&langType=auto&appKey=%s&dicts=%s&salt=%s&sign=%s&curtime=%s&docType=json",
        encodedInput, API_KEY, option, salt, sign_string, curtime_str);

    return 0;
}

int makeRequest(char *option) {
    struct data response_data = { NULL, 0 };

    CURL *curl = NULL;
    CURLcode res;

    char input[100];
    printf("Input your word:\n");
    if (scanf("%99s", input) != 1) {
        fprintf(stderr, "Failed to read input\n");
        return 1;
    }

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to init curl\n");
        curl_global_cleanup();
        return 1;
    }

    char *encoded_input = curl_easy_escape(curl, input, 0);
    if (!encoded_input) {
        fprintf(stderr, "Failed to URL encode input\n");
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 1;
    }

    char salt[37];
    buildUUID(salt);

    char postfields[512];
    if (buildPostFields(postfields, sizeof(postfields), encoded_input, option, salt, input) != 0) {
        curl_free(encoded_input);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 1;
    }

    printf("POSTFIELDS: %s\n", postfields);

    curl_easy_setopt(curl, CURLOPT_URL, "https://openapi.youdao.com/v2/dict");
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleMemory);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    res = curl_easy_perform(curl);

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    printf("HTTP response code: %ld\n", http_code);

    if (res != CURLE_OK) {
        fprintf(stderr, "Curl error: %s\n", curl_easy_strerror(res));
    } else if (response_data.response == NULL || response_data.size == 0) {
        fprintf(stderr, "No response data received.\n");
    } else {
        printf("Response: %s\n", response_data.response);
    }

    curl_free(encoded_input);
    free(response_data.response);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
