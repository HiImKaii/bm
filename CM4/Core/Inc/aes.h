#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <stddef.h>

#define AES_BLOCK_SIZE 16  // Khối dữ liệu đầu ra/vào; 16 bytes = 128 bits
#define AES_KEY_SIZE 32    // Kích thước khoá; 128-bit key
#define AES_ROUND_KEY_SIZE 240

//void InvShiftRows(uint8_t state[4][4]);
//void InvSubBytes(uint8_t state[4][4]);
//void InvMixColumns(uint8_t state[4][4]);


typedef struct {
    uint8_t RoundKey[176]; // 11 khoá vòng, mỗi khoá 16 bits
} AES_Context;

/**
 * @brief Initialize AES context with the provided key
 * @param ctx Pointer to AES context
 * @param key Pointer to the 16-byte key
 */
void AES_Init(AES_Context *ctx, const uint8_t *key);
void AES_Encrypt(AES_Context *ctx, uint8_t *input, uint8_t *output);
void AES_Decrypt(AES_Context *ctx, uint8_t *input, uint8_t *output);


//void getInputFromKeyboard(uint8_t *buffer, size_t size);
//void printHex(const uint8_t *data, size_t size);

#endif
