#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"




/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

KCipher::KCipher() : Cipher(), key("The man went to the bank on the corner"){}
KCipher::KCipher(string key) : Cipher(), page1(key){}

void KCipher::add_key(string input_key) {
	if (!p_truth) {
		pages.push_back(page1);
		p_truth = 1;
	}
	pages.push_back(input_key);
}

void KCipher::set_id(int number) {
	key = pages[number];
}

string KCipher::padKey(string key, int length) {
	string padded_key = "";
	for (int i = 0; i<length; i++) {
		padded_key[i] = key[i];
	}
        return padded_key;
}

string KCipher::applyRunningKey(string message, string key, int direction) {
	string result = message;
	for (size_t i = 0; i<message.length(); i++) {
		if (isalpha(message[i])) {
			result[i] = LOWER_CASE(result[i]);
			int key_offset = key[i%key.length()] - 'a';
			int message_offset = result[i] - 'a';
			int result_offset = (message_offset + (direction * key_offset)) % 26;
			result[i] = 'a' + result_offset;
			}
	}		
	return result;
	}

string KCipher::encrypt(string raw) {
	string padded = padKey(key, raw.length());
	return applyRunningKey(raw, padded, 1);
	}

string KCipher::decrypt(string encrypted) {
	string padded = padKey(key, encrypted.length());
	return applyRunningKey(encrypted, padded, -1);
	}



