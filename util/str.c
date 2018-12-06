#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "str.h"

/**
 * makes a string (string_t) wrapper for a supplied
 * raw char * string
 *
 * opts should be a bitwise or of any of the 3 string opts
 * defined in str.h
 *
 * len is only used if the STRING_IS_TEXT opt is not supplied
 */
string_t *make_string(char *s, char opts, size_t len) {
	if (!s) return 0;
	bool is_text = (opts & STRING_IS_TEXT);
	size_t s_len = is_text ? strlen(s) : len;
	string_t *ret = malloc(sizeof(string_t));
	if (!ret) return 0;
	*ret = (string_t){0, s_len, opts};

	if (opts & STRING_IS_COPY) {
		opts |= STRING_OWNS_S;
		ret->opts = opts;
	} else {
		ret->s = s;
		return ret;
	}

	size_t to_alloc = is_text ? s_len + 1 : s_len;
	ret->s = malloc(to_alloc);
	if (!(ret->s)) {
		free(ret);
		return 0;
	}

	strncpy(ret->s, s, to_alloc);
	return ret;
}

string_t *raw_to_text(string_t *s) {
	return 0; // TODO
}

string_t *text_to_raw(string_t *s) {
	return 0; // TODO
}

void dispose_string(string_t *ss) {
	if (!ss) return;
	if (ss->opts & STRING_OWNS_S) free(ss->s);
	free(ss);
}