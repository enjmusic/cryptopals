#include <stdlib.h>
#include "xor_crypto.h"
#include "conversions.h"

string_t *fixed_xor_hex_string(string_t *str1, string_t *str2) {
	if (str1->l != str2->l) return 0;
	char *out_str = malloc(str1->l + 1);
	if (!out_str) return 0;
	for (size_t i = 0; i < str1->l; ++i) {
		out_str[i] = value_to_hex_char(hex_char_to_value(str1->s[i]) ^ hex_char_to_value(str2->s[i]));
	}
	out_str[str1->l] = 0;
	string_t *ret = make_string(out_str, STRING_OWNS_S);
	if (!ret) free(out_str);
	return ret;
}