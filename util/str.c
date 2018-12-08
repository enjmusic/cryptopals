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
 */
string_t *make_string(char *s, char opts) {
	if (!s) return 0;
	size_t s_len = strlen(s);
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

	ret->s = malloc(s_len + 1);
	if (!(ret->s)) {
		free(ret);
		return 0;
	}

	strncpy(ret->s, s, s_len + 1);
	return ret;
}

void dispose_string(string_t *ss) {
	if (!ss) return;
	if (ss->opts & STRING_OWNS_S) free(ss->s);
	free(ss);
}