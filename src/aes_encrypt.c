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

size_t AES_CBC_Encrypt(AES* aes, void* _data, size_t size, void* _iv)
{
	uint8_t* data = _data;
	uint8_t* iv   = _iv;

	size_t encrypted = 0;

	while (size >= AES_BLOCK_SIZE)
	{
		for (size_t i = 0; i < AES_BLOCK_SIZE; i++) { data[i] ^= iv[i]; }
		encrypt(aes, data);
		for (size_t i = 0; i < AES_BLOCK_SIZE; i++) { iv[i] = data[i]; }

		encrypted += AES_BLOCK_SIZE;
		size -= AES_BLOCK_SIZE;
		data += AES_BLOCK_SIZE;
	}
	return encrypted;
}
