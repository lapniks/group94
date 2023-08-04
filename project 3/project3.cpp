#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

void sha256_length_extension(const unsigned char* original_message, const unsigned char* original_hash, const unsigned char* extension, const unsigned char* new_data, unsigned char* forged_hash) {

    size_t original_length = strlen(original_message) * 8;


    memcpy(forged_hash, original_hash, SHA256_DIGEST_LENGTH);


    size_t padded_data_length = strlen(extension) + strlen(new_data);
    unsigned char* padded_data = malloc(padded_data_length);
    memcpy(padded_data, extension, strlen(extension));
    memcpy(padded_data + strlen(extension), new_data, strlen(new_data));


    size_t new_length = original_length + strlen(extension) + padded_data_length * 8;


    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    ctx.h[0] = (uint32_t)(((uint32_t)forged_hash[0] << 24) | ((uint32_t)forged_hash[1] << 16) | ((uint32_t)forged_hash[2] << 8) | (uint32_t)forged_hash[3]);
    ctx.h[1] = (uint32_t)(((uint32_t)forged_hash[4] << 24) | ((uint32_t)forged_hash[5] << 16) | ((uint32_t)forged_hash[6] << 8) | (uint32_t)forged_hash[7]);
    ctx.h[2] = (uint32_t)(((uint32_t)forged_hash[8] << 24) | ((uint32_t)forged_hash[9] << 16) | ((uint32_t)forged_hash[10] << 8) | (uint32_t)forged_hash[11]);
    ctx.h[3] = (uint32_t)(((uint32_t)forged_hash[12] << 24) | ((uint32_t)forged_hash[13] << 16) | ((uint32_t)forged_hash[14] << 8) | (uint32_t)forged_hash[15]);
    ctx.h[4] = (uint32_t)(((uint32_t)forged_hash[16] << 24) | ((uint32_t)forged_hash[17] << 16) | ((uint32_t)forged_hash[18] << 8) | (uint32_t)forged_hash[19]);
    ctx.h[5] = (uint32_t)(((uint32_t)forged_hash[20] << 24) | ((uint32_t)forged_hash[21] << 16) | ((uint32_t)forged_hash[22] << 8) | (uint32_t)forged_hash[23]);
    ctx.h[6] = (uint32_t)(((uint32_t)forged_hash[24] << 24) | ((uint32_t)forged_hash[25] << 16) | ((uint32_t)forged_hash[26] << 8) | (uint32_t)forged_hash[27]);
    ctx.h[7] = (uint32_t)(((uint32_t)forged_hash[28] << 24) | ((uint32_t)forged_hash[29] << 16) | ((uint32_t)forged_hash[30] << 8) | (uint32_t)forged_hash[31]);
    ctx.Nl = new_length;
    ctx.data = padded_data;

    SHA256_Update(&ctx, padded_data, padded_data_length);


    SHA256_Final(forged_hash, &ctx);


    free(padded_data);
}

int main() {
    const unsigned char* original_message = "Hello, World!";
    const unsigned char* extension = "MyExt";
    const unsigned char* new_data = "Data";

    unsigned char original_hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, original_message, strlen(original_message));
    SHA256_Final(original_hash, &ctx);

    unsigned char forged_hash[SHA256_DIGEST_LENGTH];
    sha256_length_extension(original_message, original_hash, extension, new_data, forged_hash);

    printf("Original Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", original_hash[i]);
    }
    printf("\n");

    printf("Forged Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", forged_hash[i]);
    }
    printf("\n");

    return 0;
}