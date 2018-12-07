#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

#include <stdbool.h>
#include "str.h"

char value_to_base64_char(uint8_t val);

uint8_t hex_char_to_value(char c);

char value_to_hex_char(uint8_t val);

string_t *hex_to_base64(string_t *s, bool output_as_text);

#endif /* __CONVERSIONS_H__ */