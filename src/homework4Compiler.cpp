//============================================================================
// Name        : homework4Compiler.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
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

LexAnalyzer(istream& infile)
// pre: parameter refers to open data file consisting of token and lexeme pairs
//          i.e.  t_and and t_begin begin t_boolean boolean t_break break
// post: tokenmap has been populated
{
	if(!infile)
	{
		cout << "error opening file" << endl;
		exit(-1);
	}
	do //read data for lexeme/token pairs
	{
		//insert lexemes
		string lexeme;
		infile >> lexeme;

		//insert token
		string token;
		infile >> token;
		cout << lexeme << " " << token << endl;

		//add to map
		tokenmap.insert(pair<string, string>(lexeme, token));
	}
	while(!infile.eof());

}

void scanFile(istream& infile, ostream& outfile)
// pre: 1st parameter refers to an open text file that contains source code in the
//         language, 2nd parameter refers to an open empty output file
	// post: the token and lexeme pairs for the given input file have been written to
	//          the output file.  If there is an error, the incomplete token/lexeme pairs,
// 	as well as an error message have printed to the output file.  A success or
// 	fail message has printed to the console.
{
//read infile one line at a time
	if(!infile)
	{
		cout << "error opening file" << endl;
		exit(-1);
	}
	do //read data for lexeme/token pairs
	{
		cout <<"in scanFile Loop"<< endl;
		//insert lexemes
		string line;
		getline(infile, line);
		cout << "line is" << line << endl;

		//delimit to get "chunks"
		string word;
		for(int i=0; i<line.size(); i++)
		{
		cout << "in word loop" << endl;
		word.push_back(line[i]);
		cout << word << endl;
		}
	}
	while(!infile.eof());


//identify chunks as keywords, types, or identifiers
//add lexeme and token to vectors
//continue search loop

//print out to outputFile

}
};

int main()
{
	//inputting names of data files
	string sourceCodeName;
	//cout << "Enter the name of the source code file: ";
	//cin >> sourceCodeName;
	ifstream sourceCode("sourceCodeInput.txt");

	string lexemeDataFileName;
	//cout << "Enter the name of the lexeme data file: ";
	//cin >> lexemeDataFileName;
	ifstream lexemeData("tokenlexemedata.txt");

	string outputFileName;
	//cout << "Enter the name of the output file: ";
	//cin >> outputFileName;
	ofstream output("outputFile.txt");

	LexAnalyzer lexAnalyzer(lexemeData);
	lexAnalyzer.scanFile(sourceCode, output);
	return 0;
}


