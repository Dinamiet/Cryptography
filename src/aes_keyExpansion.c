#include "aes_keyExpansion.h"

#include "aes_lookup.h"

static uint32_t subWord(uint32_t word);
static uint32_t rotWord(uint32_t word);

static uint32_t subWord(uint32_t word)
{
	uint32_t sword = 0;
	for (size_t i = 0; i < WORD_SIZE; i++)
	{
		uint8_t byte = (uint8_t)(word >> (i * BITS_IN_BYTE));
		sword |= sbox[byte] << (i * BITS_IN_BYTE);
	}
	return sword;
}

static uint32_t rotWord(uint32_t word) { return (word >> ((WORD_SIZE - 1) * BITS_IN_BYTE)) | (word << (BITS_IN_BYTE)); }

void keyExpansion(void* _expandedKey, void* _key, size_t keySize, size_t numRounds)
{
	uint8_t*  expandedByte = _expandedKey;
	uint32_t* expandedWord = _expandedKey;
	uint8_t*  key          = _key;
	size_t    Nk           = keySize / WORD_SIZE;
	size_t    i            = 0;
	while (i <= Nk - 1)
	{
		for (size_t k = 0; k < WORD_SIZE; k++) { expandedByte[WORD_SIZE * i + k] = key[WORD_SIZE * i + k]; }
		++i;
	}

	while (i <= 4 * numRounds + 3)
	{
		uint32_t temp = BIG_ENDIAN_32(expandedWord[i - 1]);
		if (i % Nk == 0)
			temp = subWord(rotWord(temp)) ^ (rcon[i / Nk] << ((WORD_SIZE - 1) * BITS_IN_BYTE));
		else if (Nk > 6 && i % Nk == WORD_SIZE)
			temp = subWord(temp);
		expandedWord[i] = expandedWord[i - Nk] ^ BIG_ENDIAN_32(temp);
		++i;
	}
}
