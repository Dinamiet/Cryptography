#ifndef _AES_H_
#define _AES_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define AES_BLOCK_SIZE 16

typedef enum _AESKeyOption_
{
	AES_128,
	AES_192,
	AES_256,
} AESKeyOption;

typedef struct _AES_
{
	size_t  Rounds;
	uint8_t IV[AES_BLOCK_SIZE];
	uint8_t ExpandedKey[240];
} AES;

void AES_Init(AES* aes, void* iv, void* key, AESKeyOption option);
size_t AES_CBC_Encrypt(AES* aes, void* data, size_t size, bool addPadding);

#endif
