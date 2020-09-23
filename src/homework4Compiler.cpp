//============================================================================
// Name        : homework4Compiler.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include<map>
using namespace std;

class LexAnalyzer
{
private:
	vector<string> lexemes;   // a string of lexemes that correspond to the input file
	vector<string> tokens;      // a string of tokens that correspond to the input file
	map<string, string> tokenmap;   // a map structure that maps lexemes to their
					    // corresponding tokens for easy look up
	// other private methods
public:

LexAnalyzer(istream& infile);
// pre: parameter refers to open data file consisting of token and lexeme pairs
//          i.e.  t_and and t_begin begin t_boolean boolean t_break break
// post: tokenmap has been populated

void scanFile(istream& infile, ostream& outfile);
// pre: 1st parameter refers to an open text file that contains source code in the
//         language, 2nd parameter refers to an open empty output file
	// post: the token and lexeme pairs for the given input file have been written to
	//          the output file.  If there is an error, the incomplete token/lexeme pairs,
// 	as well as an error message have printed to the output file.  A success or
// 	fail message has printed to the console.
};

int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}


