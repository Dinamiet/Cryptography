#ifndef _AES_KEY_EXPANSION_H_
#define _AES_KEY_EXPANSION_H_

#include "aes.h"

void keyExpansion(void* _expandedKey, void* _key, size_t keySize, size_t numRounds);

#endif
