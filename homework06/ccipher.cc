#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation


// -------------------------------------------------------

CCipher::CCipher() : Cipher(){};

CCipher::CCipher(int offset) : Cipher(), offset(offset){};

CCipher::~CCipher(){};

string CCipher::encrypt(string raw) {
	rotate_string(raw, offset);
	return raw;
}

string CCipher::decrypt(string encrypted) {
	rotate_string(encrypted, 26-offset);
	return encrypted;
}

// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
	if (rot < 0) {
		rot += 26;
	}
	std::cout << rot << std::endl;

	int length = in_str.size();
	for (int i = 0; i<length; i++) {
		char current = UPPER_CASE(in_str[i]);
		char rotated = ((current-'A')+rot) % 26 + 'A';
		if(in_str[i]>='a' && in_str[i] <= 'z') {
			in_str[i] = LOWER_CASE(rotated);
		}
		else if (in_str[i]>='A' && in_str[i] <= 'Z') {
			in_str[i] = rotated;
		}
	}
}

