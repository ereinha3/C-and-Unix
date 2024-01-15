#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"


// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

VCipher::VCipher() : key("FORTIFICATION"){}

VCipher::VCipher(string key) : key(key){}
/*
string VigenereCipher::encrypt(string raw){
	string encrypted;
	for (int i=0; i<raw.length(); i++) {
		if (isalpha(raw[i])){
			raw[i] = LOWER_CASE(raw[i]);
			int index = i%key.length();
			int offset_key = key[index] - 'a';
			int offset_raw = raw[i] - 'a';
			int enc_offset = (offset_key + offset_raw)%26;
			encrypted[i] = 'a'+enc_offset;
		}
	}
	return encrypted;
}

string VigenereCipher::decrypt(string e){
	string dec;
	for (int i=0; i<e.length(); i++) {
		if (isalpha(e[i])){
			e[i] = LOWER_CASE(e[i]);
			int index = i%key.length();
			int offset_key = key[index] - 'a';
			int offset_raw = e[i] - 'a';
			int enc_offset = (offset_raw - offset_key)%26;
			dec[i] = 'a'+enc_offset;
		}
	}
	return dec;
}
*/	
