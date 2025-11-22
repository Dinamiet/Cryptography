#include "aes.h"
#include "aes_rounds.h"

#include <stdio.h>

void print_matrix(char* Name, size_t round, uint8_t* values)
{
	printf("-------------------\n");
	printf("%s(%ld):\n", Name, round);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 16 / 4; ++j) { printf("%2.2x ", values[4 * j + i]); }
		printf("\n");
	}
	printf("-------------------\n");
}

static void encrypt(AES* aes, void* data);

static void encrypt(AES* aes, void* data)
{
	size_t round = 0;
	addRoundKey(data, aes->ExpandedKey, round++);

	print_matrix("addRoundKey", round, data);

	while (round <= aes->Rounds)
	{
		subbytes(data);
		print_matrix("subBytes", round, data);

		shiftRows(data);
		print_matrix("shiftRows", round, data);

		if (round < aes->Rounds)
		{
			mixColumns(data);
			print_matrix("mixColumns", round, data);
		}

		addRoundKey(data, aes->ExpandedKey, round++);
		print_matrix("addRoundKey", round, data);
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
