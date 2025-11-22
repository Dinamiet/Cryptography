#ifndef _AES_LOOKUP_H_
#define _AES_LOOKUP_H_

#include <stdint.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define BIG_ENDIAN_16(x)    __builtin_bswap16(x)
#define LITTLE_ENDIAN_16(x) (x)
#define BIG_ENDIAN_32(x)    __builtin_bswap32(x)
#define LITTLE_ENDIAN_32(x) (x)
#else
#define BIG_ENDIAN_16(x)    (x)
#define LITTLE_ENDIAN_16(x) __builtin_bswap16(x)
#define BIG_ENDIAN_32(x)    (x)
#define LITTLE_ENDIAN_32(x) __builtin_bswap32(x)
#endif

#define BITS_IN_BYTE 8
#define WORD_SIZE 4

extern const uint8_t sbox[];
extern const uint8_t rcon[];

extern const uint8_t mix_col_2[];
extern const uint8_t mix_col_3[];

#endif
