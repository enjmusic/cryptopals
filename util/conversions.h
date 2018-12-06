#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

#include <stdbool.h>
#include "str.h"

string_t *hex_to_base64(string_t *s, bool output_as_text);

#endif /* __CONVERSIONS_H__ */