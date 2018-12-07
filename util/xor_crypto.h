#ifndef __XOR_CRYPTO_H__
#define __XOR_CRYPTO_H__

#include <stdbool.h>
#include "str.h"

string_t *fixed_xor_hex_string(string_t *str1, string_t *str2, bool output_as_text);

#endif /* __XOR_CRYPTO_H__ */