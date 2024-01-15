#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

const unsigned int MAX_LENGTH = 100;

/* A class that implements a
   Running key cipher class. It 
   inherts class Cipher */
class KCipher : public Cipher {
	public:
		KCipher();
		KCipher(string key);
		virtual ~KCipher() {};
		string encrypt(string raw) override;
		string decrypt(string encrypted) override;
		void set_id(int num);
		void add_key(string key);
		void padKey(string input);
	private:
		string key;
		int page_number = 0;
		vector<string> pages;
};
#endif

