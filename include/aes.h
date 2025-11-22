#ifndef _AES_H_
#define _AES_H_

#include <stddef.h>
#include <stdint.h>

typedef enum _AESKeyOption_
{
	AES_128,
	AES_192,
	AES_256,
} AESKeyOption;

typedef struct _AES_
{
	size_t  Rounds;
	uint8_t ExpandedKey[240];
} AES;

void AES_Init(AES* aes, void* key, AESKeyOption option);

#endif
