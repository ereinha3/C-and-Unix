#ifndef CCIPHER_H_
#define CCIPHER_H_
#include "cipher.h"

using namespace std;

/* A class that implements a
   Caesar cipher class. It 
   inherits the Cipher class */
class CCipher: Cipher {
	public:
		CCipher();
		CCipher(int offset);
		~CCipher();
		string encrypt(string raw) override;
		string decrypt(string encrypted) override;
	private:
		int offset;
};

/* Helper function headers 
 */
void rotate_string(string& in_str, int rot);
#endif

