/*************************************

CIS330: Lab 6

The goal of this lab is to use C++ classes and inheritance to create simple
letter filters.

Instructions:

(1) Read this file and understand the basic operations and interactions
    between these objects.
(2) Define and implement the ToLower class as described below.
(3) Modify `getFilter` to test your ToLower class.
(4) Define and implement the Encrypt class as described below.
(5) Modify `getFilter` to test your Encrypt class.
      Note: If you want to verify your Encrypt filter, instantiate with a
            shift of 13 and pipe a message through the filter twice.

*************************************/

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Filter
{
  virtual char FilterLetter(char ch) { return ch; }

public:
  string Exec(string input);
};

string Filter::Exec(string input)
{
  stringstream res;
  for (int i = 0; i < input.size(); i++) {

    if (isalpha(input[i])) {

      res << FilterLetter(input[i]);

    } else {

      res << input[i];
    }
  }
  return res.str();
}

class ToUpper : public Filter
{
  char FilterLetter(char ch) { return toupper(ch); }
};

class ToLower : public Filter
{
	char FilterLetter(char ch) {return tolower(ch);}
};

char
shift_cypher(char ch, int offset)
{
  return (toupper(ch) - 'A' + offset) % 26 + 'A';
}

class Encrypt : public Filter
{
	char FilterLetter(char ch){ return shift_cypher(ch, offset);}
	public:
		Encrypt(int i_offset) {offset=i_offset;}
	private:
		int offset;
};

Filter * getFilter()
{
  return new Encrypt(13);
}

int
main()
{
  string temp;

  Filter *theFilter = getFilter();

  while (getline(cin, temp)) {
    cout << theFilter->Exec(temp) << endl;
  }

  return 0;
}
