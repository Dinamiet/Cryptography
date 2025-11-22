#include "aes_keyExpansion.h"

#include "aes_lookup.h"

static uint32_t subRcon(uint32_t word, size_t itt);

static uint32_t subRcon(uint32_t word, size_t itt)
{
	// Rotate
	word = (word >> (3 * BITS_IN_BYTE)) | (word << (BITS_IN_BYTE));

	uint32_t sword = 0;
	for (size_t i = 0; i < sizeof(sword); i++)
	{
		uint8_t byte = (uint8_t)(word >> (i * BITS_IN_BYTE));
		sword |= sbox[byte] << (i * BITS_IN_BYTE);
	}

	sword ^= rcon[itt] << ((sizeof(sword) - 1) * BITS_IN_BYTE);
	return sword;
}

void keyExpansion(uint8_t* expandedKey, uint8_t* key, size_t keySize, size_t expandedSize)
{
	for (size_t i = 0; i < keySize; i++) { expandedKey[i] = key[i]; }

	size_t rcon_itt = 1;

	size_t expandProgress = keySize;
	while (expandProgress < expandedSize)
	{
		uint32_t t = 0;
		for (size_t i = 0; i < sizeof(t); i++)
		{
			uint8_t byte = expandedKey[(expandProgress - sizeof(t)) + i];
			t += byte << ((sizeof(t) - (i + 1)) * BITS_IN_BYTE);
		}

		if (expandProgress % keySize == 0)
			t = subRcon(t, rcon_itt++);

		if (keyOption == AES_256 && expandProgress % keySize == 16)
		{
			uint32_t t_new = 0;
			for (size_t i = 0; i < sizeof(t); i++)
			{
				uint8_t byte = (uint8_t)(t >> (i * BITS_IN_BYTE));
				t_new += sbox[byte] << (i * BITS_IN_BYTE);
			}
			t = t_new;
		}

		for (size_t i = 0; i < sizeof(t); i++)
		{
			uint8_t byte                = (uint8_t)(t >> ((sizeof(t) - (i + 1)) * BITS_IN_BYTE));
			expandedKey[expandProgress] = expandedKey[expandProgress - keySize] ^ byte;
			++expandProgress;
		}
	}
}
