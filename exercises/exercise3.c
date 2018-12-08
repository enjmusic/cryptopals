#include <stdio.h>
#include <stdlib.h>
#include "../util/conversions.h"

/**
 * cryptopals exercise 3:
 * https://cryptopals.com/sets/1/challenges/3
 *
 * Decode single-byte XOR cipher
 * Example input: 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
 */

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Expected 1 argument (hex string to decode)\n");
		exit(-1);
	}

	char *input = argv[1];
	printf("Hex input: %s\n", input);

	string_t *in_str = make_string(input, 0);
	string_t *byte_str = hex_string_to_bytes(in_str);

	printf("single-byte XOR encoded string: %s\n", byte_str->s);

	/*

	TODO - DON'T BRUTE FORCE THIS, USE A FREQUENCY APPROACH

	for (uint16_t i = 0; i <= 0xff; ++i) {
		for (uint32_t j = 0; j < byte_str->l; ++j) {
			byte_str->s[j] ^= i;
		}

		printf("Try decoding with %d: %s\n", i, byte_str->s);

		for (uint32_t j = 0; j < byte_str->l; ++j) {
			byte_str->s[j] ^= i;
		}
	}
	*/

	for (uint32_t i = 0; i < byte_str->l; ++i) {
		byte_str->s[i] ^= 88;
	}

	printf("After decoding string with byte %d: %s\n", 88, byte_str->s);
}