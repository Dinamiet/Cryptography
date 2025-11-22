#ifndef _AES_ROUNDS_H_
#define _AES_ROUNDS_H_

#include <stddef.h>

void subbytes(void* data);
void shiftRows(void* data);
void mixColumns(void* data);
void addRoundKey(void* data, void* extendedKey, size_t round);

#endif
