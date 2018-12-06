#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include "conversions.h"

static char base64_table[64] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

char value_to_base64_char(uint8_t val) {
	assert(val < 0x40);
	return base64_table[val];
}

uint8_t hex_char_to_value(char c) {
	if (c >= 48 && c <= 57) { // 0-9
		return (uint8_t)(c - 48);
	} else if (c >= 97 && c <= 102) { // a-f
		return (uint8_t)(c - 87); // - 97 + 10
	} else { // Invalid hex char
		assert(0);
		return 0; // Unreachable
	}
}

string_t *hex_to_base64(string_t *s, bool output_as_text) {
	if (!s) return 0;

	// Make sure output length is [smallest multiple of 4] >= s->l * 2/3
	// 2/3 and not 4/3 because every 2 chars of the input string is 1 byte (hex)
	bool input_is_odd_length = (s->l & 0x1);
	size_t output_length = ((input_is_odd_length ? s->l + 1 : s->l) * 2) / 3;
	if (output_length & 0x3) output_length += 0x4 - (output_length & 0x3);
	char *out_str = malloc(output_as_text ? output_length + 1 : output_length);
	if (!out_str) return 0;

	// Start conversion (padding beginning with a 0 if we have an odd-length hex string)
	size_t in_offset = 0;
	size_t out_offset = input_is_odd_length;
	bool halfway_in = input_is_odd_length;
	uint8_t cached_hex_value = input_is_odd_length ? hex_char_to_value(s->s[0]) : 0;
	if (input_is_odd_length) {
		out_str[0] = value_to_base64_char((cached_hex_value & 0xc) >> 2);
	}

	while (in_offset < s->l && out_offset < output_length) {
		uint8_t to_convert = 0;
		char hex_char_to_pass = '0';

		if (halfway_in) {
			// Converting from halfway through a hex char
			to_convert = (cached_hex_value & 0x3) << 4;
			if (++in_offset < s->l) hex_char_to_pass = s->s[in_offset];
			to_convert |= hex_char_to_value(hex_char_to_pass);
			in_offset++;
			halfway_in = 0;
		} else {
			// Converting from start of a hex char
			if (in_offset < s->l) hex_char_to_pass = s->s[in_offset++];
			to_convert = hex_char_to_value(hex_char_to_pass) << 2;
			hex_char_to_pass = (in_offset < s->l) ? s->s[in_offset] : '0';
			cached_hex_value = hex_char_to_value(hex_char_to_pass);
			to_convert |= (cached_hex_value & 0xc) >> 2;
			halfway_in = 1;
		}

		out_str[out_offset++] = value_to_base64_char(to_convert);
	}

	// Pad remainder of last 4 base64 chars with = character if needed
	while (out_offset < output_length) out_str[out_offset++] = '=';

	if (output_as_text) out_str[output_length] = 0;
	char string_flags = STRING_OWNS_S | (output_as_text ? STRING_IS_TEXT : 0);
	return make_string(out_str, string_flags, output_length);
}