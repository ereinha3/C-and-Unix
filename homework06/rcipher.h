#ifndef RCIPHER_H_ 
#define RCIPHER_H_
#include "ccipher.h"

using namespace std;

/* A class that implements a
   ROT13 cipher class. It 
   inherts class CCipher */
class RCipher : public CCipher {
	public:
		RCipher();
		~RCipher();
	private:
		int offset = 13;
};
#endif

