#include <stdio.h>
#include <stdlib.h>
#include "../util/conversions.h"

/**
 * cryptopals exercise 1:
 * https://cryptopals.com/sets/1/challenges/1
 *
 * Convert hex string to base64
 * Example input: 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
 * Example output: SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
 */

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Expected 2nd argument (hex string to convert)\n");
		exit(-1);
	}

	char *input = argv[1];
	printf("Hex input: %s\n", input);
	
	string_t *in_str = make_string(input, 0);
	string_t *converted_str = hex_to_base64(in_str);

	printf("Base64 output: %s\n", converted_str->s);

	dispose_string(in_str);
	dispose_string(converted_str);
}