#ifndef __STRING_H__
#define __STRING_H__

#define STRING_OWNS_S 			0x1 /* SHOULD FREE S ON DISPOSE */
#define STRING_IS_COPY			0x2 /* WAS COPIED FROM ANOTHER STRING */

typedef struct string_s {
	char *s;
	size_t l;
	char opts; /* BITWISE OR OF SOME ABOVE DEFS */
} string_t;

string_t *make_string(char *s, char opts);

void dispose_string(string_t *ss);

#endif /* __STRING_H__ */