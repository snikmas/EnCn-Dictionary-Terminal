#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main(void) {
    char *userInput = "nameISnumberOne";
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    // Create a message digest context
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        perror("EVP_MD_CTX_new");
        return 1;
    }

    // Initialize the digest context for SHA-256
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
        perror("EVP_DigestInit_ex");
        return 1;
    }

    // Hash the input
    if (EVP_DigestUpdate(mdctx, userInput, strlen(userInput)) != 1) {
        perror("EVP_DigestUpdate");
        return 1;
    }

    // Finalize the hash
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        perror("EVP_DigestFinal_ex");
        return 1;
    }

    // Free the context
    EVP_MD_CTX_free(mdctx);

    // Convert to hex string
    char sign[hash_len * 2 + 1];
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(sign + (i * 2), "%02x", hash[i]);
    }
    sign[hash_len * 2] = '\0';

    printf("%s\n", sign);

    return 0;
}
