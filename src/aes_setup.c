#include "aes.h"
#include "aes_keyExpansion.h"

#include <string.h>

void AES_Init(AES* aes, void* iv, void* key, AESKeyOption option)
{
	size_t keySize = 0;
	switch (option)
	{
		case AES_128:
			aes->Rounds = 10;
			keySize = 16;
			break;

		case AES_192:
			aes->Rounds = 12;
			keySize = 24;
			break;

		case AES_256:
			aes->Rounds = 14;
			keySize = 32;
			break;
	}

	memset(aes->ExpandedKey, 0, 240);
	keyExpansion(aes->ExpandedKey, key, keySize, aes->Rounds);
	memcpy(aes->IV, iv, sizeof(aes->IV));
}
