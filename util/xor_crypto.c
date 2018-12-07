#include <stdlib.h>
#include "xor_crypto.h"
#include "conversions.h"

string_t *fixed_xor_hex_string(string_t *str1, string_t *str2, bool output_as_text) {
	if (str1->l != str2->l) return 0;
	char *out_str = malloc(output_as_text ? str1->l + 1 : str1->l);
	if (!out_str) return 0;
	for (size_t i = 0; i < str1->l; ++i) {
		out_str[i] = value_to_hex_char(hex_char_to_value(str1->s[i]) ^ hex_char_to_value(str2->s[i]));
	}
	if (output_as_text) out_str[str1->l] = 0;
	char string_flags = STRING_OWNS_S | (output_as_text ? STRING_IS_TEXT : 0);
	string_t *ret = make_string(out_str, string_flags, str1->l);
	if (!ret) free(out_str);
	return ret;
}