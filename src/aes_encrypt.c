#include "aes.h"
#include "aes_rounds.h"

#include <string.h>

static void encrypt(AES* aes, void* data);

static void encrypt(AES* aes, void* data)
{
	size_t round = 0;
	addRoundKey(data, aes->ExpandedKey, round++);

	while (round <= aes->Rounds)
	{
		subbytes(data);

		shiftRows(data);

		if (round < aes->Rounds)
			mixColumns(data);

		addRoundKey(data, aes->ExpandedKey, round++);
	}
}

size_t AES_CBC_Encrypt(AES* aes, void* _data, size_t size, bool addPadding)
{
	uint8_t* data = _data;

	size_t encrypted = 0;

	uint8_t block[AES_BLOCK_SIZE];
	while (size)
	{
		if (size < AES_BLOCK_SIZE)
		{
			if (addPadding)
			{
				memset(block, 0, sizeof(block));
				memcpy(block, data, size);
			}
			else
				break;
		}
		else
		{
			memcpy(block, data, sizeof(block));
		}
		for (size_t i = 0; i < AES_BLOCK_SIZE; i++) { block[i] ^= aes->IV[i]; }
		encrypt(aes, data);
		for (size_t i = 0; i < AES_BLOCK_SIZE; i++) { aes->IV[i] = block[i]; }

		encrypted += AES_BLOCK_SIZE;
		size -= AES_BLOCK_SIZE;
		data += AES_BLOCK_SIZE;
	}

	return encrypted;
}
