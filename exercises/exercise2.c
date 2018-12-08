#include <stdio.h>
#include <stdlib.h>
#include "../util/xor_crypto.h"

/**
 * cryptopals exercise 2:
 * https://cryptopals.com/sets/1/challenges/2
 *
 * Fixed XOR
 * Example input 1: 1c0111001f010100061a024b53535009181c
 * Example input 2: 686974207468652062756c6c277320657965
 * Example output: 746865206b696420646f6e277420706c6179
 */

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Expected 2 arguments (hex strings to XOR)\n");
		exit(-1);
	}

	char *input1 = argv[1];
	printf("Hex input 1: %s\n", input1);

	char *input2 = argv[2];
	printf("Hex input 2: %s\n", input2);
	
	string_t *in_str1 = make_string(input1, 0);
	string_t *in_str2 = make_string(input2, 0);
	string_t *xor_str = fixed_xor_hex_string(in_str1, in_str2);

	printf("Fixed XOR output: %s\n", xor_str->s);

	dispose_string(in_str1);
	dispose_string(in_str2);
	dispose_string(xor_str);	
}