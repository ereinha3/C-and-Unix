#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"




/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

KCipher::KCipher() : Cipher(){}
KCipher::KCipher(string key) : Cipher(), key(key){}


string KCipher::encrypt(string raw) {
	cout << "Encrypting...";
	string encrypted;
	if (this->key.empty()) {
		return raw;
	}
	padKey(raw);
	int length = raw.length();
	for (int i =0; i<length; i++) {
		char rchar = raw[i];
		char kchar = this->key[i];
		encrypted += (rchar+kchar)%26;
	}
	cout << "DONE!" << endl;
	return encrypted;
}

string KCipher::decrypt(string encrypted) {
	cout << "Decrypting...";
	string decrypted;
	if (this->key.empty()) {
		return encrypted;
	}
	int length = encrypted.length();
	for (int i =0; i<length; i++) {
		char echar = encrypted[i];
		char kchar = this->key[i];
		decrypted += (echar+kchar)%26;
	}
	cout << "DONE!" << endl;
	return decrypted;
}

void KCipher::set_id(int num) {
	this->key = this->pages[num];
}

void KCipher::add_key(string key){
	if (this->page_number == 0) {
		this->pages[0] = key;
	}
	this->page_number += 1;
	this->pages[this->page_number] = key;
}

void KCipher::padKey(string input){
	string unpadded = this->key;
	string result;
	for (size_t i = 0; i<input.size(); i++) {
		result[i] = key[i];
	}
	this->key = result;
}


