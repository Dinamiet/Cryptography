#include "aes_rounds.h"

#include "aes.h"
#include "aes_lookup.h"

#include <stddef.h>

void subbytes(void* _data)
{
	uint8_t* data = _data;
	for (size_t i = 0; i < AES_BLOCK_SIZE; i++) { data[i] = sbox[data[i]]; }
}

void shiftRows(void* _data)
{
	uint8_t* data = _data;

	for (int i = 1; i < WORD_SIZE; ++i) // can start at 1 cause first row doesnt get shifted
	{
		for (int k = 0; k < i; ++k) // number of shifts
		{
			uint8_t tmp = data[i];
			for (int j = 0; j < WORD_SIZE - 1; ++j) { data[WORD_SIZE * j + i] = data[WORD_SIZE * (j + 1) + i]; }
			data[WORD_SIZE * 3 + i] = tmp;
		}
	}
}

void mixColumns(void* _data)
{
	uint8_t* data = _data;
	for (size_t i = 0; i < AES_BLOCK_SIZE; i += WORD_SIZE)
	{
		uint8_t a[WORD_SIZE];
		for (size_t j = 0; j < WORD_SIZE; j++) { a[j] = data[i + j]; }
		data[i + 0] = mix_col_2[a[0]] ^ mix_col_3[a[1]] ^ a[2] ^ a[3]; // 2	3	1	1
		data[i + 1] = a[0] ^ mix_col_2[a[1]] ^ mix_col_3[a[2]] ^ a[3]; // 1	2	3	1
		data[i + 2] = a[0] ^ a[1] ^ mix_col_2[a[2]] ^ mix_col_3[a[3]]; // 1	1	2	3
		data[i + 3] = mix_col_3[a[0]] ^ a[1] ^ a[2] ^ mix_col_2[a[3]]; // 3	1	1	2
	}
}

void addRoundKey(void* _data, void* _extendedKey, size_t round)
{
	uint8_t*     data        = _data;
	uint8_t*     extendedKey = _extendedKey;
	const size_t l           = round * (AES_BLOCK_SIZE);
	for (size_t i = 0; i < AES_BLOCK_SIZE; i++) { data[i] ^= extendedKey[i + l]; }
}
