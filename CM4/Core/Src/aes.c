/*
 * aes.c
 *
 *  Created on: Dec 25, 2024
 *      Author: VU XUAN QUAN
 */


#include "aes.h"
#include <string.h>

static const uint8_t sbox[256] = {
    // Fill in with AES s-box values
};

static const uint8_t rsbox[256] = {
    // Fill in with AES inverse s-box values
};

static const uint8_t Rcon[15] = {
    // Fill in with AES Rcon values for up to AES-256
};

static void KeyExpansion(const uint8_t *key, uint8_t *RoundKey) {
    uint32_t i, j, k;
    uint8_t temp[4];

    for (i = 0; i < 8; ++i) {
        RoundKey[i * 4 + 0] = key[i * 4 + 0];
        RoundKey[i * 4 + 1] = key[i * 4 + 1];
        RoundKey[i * 4 + 2] = key[i * 4 + 2];
        RoundKey[i * 4 + 3] = key[i * 4 + 3];
    }

    for (i = 8; i < 60; ++i) {
        temp[0] = RoundKey[(i - 1) * 4 + 0];
        temp[1] = RoundKey[(i - 1) * 4 + 1];
        temp[2] = RoundKey[(i - 1) * 4 + 2];
        temp[3] = RoundKey[(i - 1) * 4 + 3];

        if (i % 8 == 0) {
            uint8_t t = temp[0];
            temp[0] = sbox[temp[1]] ^ Rcon[i / 8];
            temp[1] = sbox[temp[2]];
            temp[2] = sbox[temp[3]];
            temp[3] = sbox[t];
        } else if (i % 8 == 4) {
            temp[0] = sbox[temp[0]];
            temp[1] = sbox[temp[1]];
            temp[2] = sbox[temp[2]];
            temp[3] = sbox[temp[3]];
        }

        RoundKey[i * 4 + 0] = RoundKey[(i - 8) * 4 + 0] ^ temp[0];
        RoundKey[i * 4 + 1] = RoundKey[(i - 8) * 4 + 1] ^ temp[1];
        RoundKey[i * 4 + 2] = RoundKey[(i - 8) * 4 + 2] ^ temp[2];
        RoundKey[i * 4 + 3] = RoundKey[(i - 8) * 4 + 3] ^ temp[3];
    }
}

static void AddRoundKey(uint8_t *state, const uint8_t *RoundKey) {
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        state[i] ^= RoundKey[i];
    }
}

static void SubBytes(uint8_t *state) {
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        state[i] = sbox[state[i]];
    }
}

static void InvSubBytes(uint8_t *state) {
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        state[i] = rsbox[state[i]];
    }
}

static void ShiftRows(uint8_t *state) {
    uint8_t temp;

    // Row 1
    temp = state[1];
    state[1] = state[5];
    state[5] = state[9];
    state[9] = state[13];
    state[13] = temp;

    // Row 2
    temp = state[2];
    state[2] = state[10];
    state[10] = temp;
    temp = state[6];
    state[6] = state[14];
    state[14] = temp;

    // Row 3
    temp = state[3];
    state[3] = state[15];
    state[15] = state[11];
    state[11] = state[7];
    state[7] = temp;
}

static void InvShiftRows(uint8_t *state) {
    uint8_t temp;

    // Row 1
    temp = state[13];
    state[13] = state[9];
    state[9] = state[5];
    state[5] = state[1];
    state[1] = temp;

    // Row 2
    temp = state[2];
    state[2] = state[10];
    state[10] = temp;
    temp = state[6];
    state[6] = state[14];
    state[14] = temp;

    // Row 3
    temp = state[3];
    state[3] = state[7];
    state[7] = state[11];
    state[11] = state[15];
    state[15] = temp;
}

static void MixColumns(uint8_t *state) {
    // Implementation of MixColumns step
}

static void InvMixColumns(uint8_t *state) {
    // Implementation of inverse MixColumns step
}
}

void AES_Init(AES_Context *ctx, const uint8_t *key) {
    KeyExpansion(key, ctx->RoundKey);
}

void AES_Encrypt(AES_Context *ctx, uint8_t *input, uint8_t *output) {
    uint8_t state[AES_BLOCK_SIZE];
    memcpy(state, input, AES_BLOCK_SIZE);

    AddRoundKey(state, ctx->RoundKey);

    for (int round = 1; round < 14; ++round) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, ctx->RoundKey + round * AES_BLOCK_SIZE);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, ctx->RoundKey + 14 * AES_BLOCK_SIZE);

    memcpy(output, state, AES_BLOCK_SIZE);
}

void AES_Decrypt(AES_Context *ctx, uint8_t *input, uint8_t *output) {
    uint8_t state[AES_BLOCK_SIZE];
    memcpy(state, input, AES_BLOCK_SIZE);

    AddRoundKey(state, ctx->RoundKey + 14 * AES_BLOCK_SIZE);

    for (int round = 13; round > 0; --round) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, ctx->RoundKey + round * AES_BLOCK_SIZE);
        InvMixColumns(state);
    }

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, ctx->RoundKey);

    memcpy(output, state, AES_BLOCK_SIZE);
}
