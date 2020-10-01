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

int inputString(istream& infile, ostream& outfile, string test, int i)
// pre: 1st parameter refers to the current file being read
//		2nd parameter refers to the output file that the tokens and lexemes are being put into
//		3rd parameter refers to a string that is being tested for quotes to open a string lexeme
//      4th parameter refers to the number of the character being tested for a quote
	// post: if the character matches a quote, the string and its token will be written
	//		 to their respective vectors
{
	string recordedString;
	while(test[i]!='”' && test[i]!='"')//if there are more things in the string
	{
		if(test[i]=='\0')
		{
			getline(infile, test);
			if(infile.eof())
			{
				lexemes.push_back(recordedString);
				tokens.push_back("t_str");
				for(int i=0; i<lexemes.size(); i++)
				{
					outfile << tokens.at(i) << " : " << lexemes.at(i) <<endl;
				}
				cout << "Error: string not closed. File read was unsuccessful." << endl;
				exit(-2);
			}
			else
			{
				i=0;
			}
		}
		recordedString.push_back(test[i]);
		i++;
	}
	lexemes.push_back(recordedString);
	tokens.push_back("t_str");
	//i++; //add one to the index to get past the ending comma
	return i;//show where we currently are on the line
}

int testLetters(string test, int i)
// pre:	1st parameter refers to a string that is being tested for keyword or id lexemes
//      2nd parameter refers to the number of the character being tested for a keyword or lexeme
		// post: if the delimited string is a keyword the lexeme and a keyword token are put in the vectors
		//		if the string is not a keyword the lexeme and an id token are put in the vectors
{
	string recordedString;
	recordedString.push_back(test[i]);
	while(isalnum(test[i+1]))
	{
		i++;
		recordedString.push_back(test[i]);

	}
	if(tokenmap.count(recordedString)>0 && recordedString!="if")//match to keyword
	{
		lexemes.push_back(recordedString);
		tokens.push_back(tokenmap[recordedString]);
	}
	else//otherwise it is an id
	{
		lexemes.push_back(recordedString);
		tokens.push_back("t_id");
	}
	return i;
}

int testDigit(ostream& outfile, string test, int i)
// pre:	1st parameter refers to the output file which the lexemes and tokens will be printed to
//		2nd parameter refers to a string that is being tested for an integer
//      3rd parameter refers to the number of the character being tested for an integer
		// post: the integer has been found and output to the vectors with the int token
{
	string recordedInteger;
	recordedInteger.push_back(test[i]);
	while(isalnum(test[i+1]))
	{
		i++;
		if(isalpha(test[i]))
		{
			lexemes.push_back(recordedInteger);
			tokens.push_back("t_int");
			for(int i=0; i<lexemes.size(); i++)
			{
				outfile << tokens.at(i) << " : " << lexemes.at(i) <<endl;
			}
			cout<< "Error: id cannot start with an integer, or integer and keyword are not delimited. File read was unsuccessful." << endl;
			exit(-3);
		}
		else
		{
			recordedInteger.push_back(test[i]);
		}
	}
	lexemes.push_back(recordedInteger);
	tokens.push_back("t_int");
	return i;
}

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
		string token;
		infile >> token;

		//insert token
		string lexeme;
		infile >> lexeme;

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
	if(!infile)//check if infile exists
	{
		cout << "error opening file" << endl;
		exit(-1);
	}
	string line;
	while(getline(infile, line))//read next line of file
	{
		for(int i=0; i<line.size(); i++)
		{
			//setup our test variables
			bool matchFound=false;
			string testSingleChar;
			testSingleChar.push_back(line[i]);
			//test the one and two character operators
			if(i+1<line.size())
			{
				string testDoubleChar;
				testDoubleChar.push_back(line[i]);
				testDoubleChar.push_back(line[i+1]);
				if(tokenmap.count(testDoubleChar)>0)//test double char
				{
					//add lexemes and tokens to vectors if you find a match
					lexemes.push_back(testDoubleChar);
					tokens.push_back(tokenmap[testDoubleChar]);
					matchFound=true;
				}
			}
			if(!matchFound)
			{
				if(tokenmap.count(testSingleChar)>0)//test single char
				{
					//add lexemes and tokens to vectors if you find a match
					lexemes.push_back(testSingleChar);
					tokens.push_back(tokenmap[testSingleChar]);
					matchFound=true;
				}
			}
			if(!matchFound)
			{
				if(line[i] == '“' || line[i] == '"')//test for strings
				{
					i++;//start reading at the first character of the string
					int index = inputString(infile, outfile, line, i);
					i = index;
					matchFound = true;
				}
			}
			if(!matchFound)
			{
				if(isdigit(line[i]))//test for integer
				{
					int index = testDigit(outfile, line, i);
					i = index;
					matchFound = true;
				}
			}
			if(!matchFound)
			{
				if(isalpha(line[i]))// test for keyword or id
				{
					int index = testLetters(line, i);
					i = index;
				}
			}
		}//end for loop
	}//end while loop
	//print to outputFile
	for(int i=0; i<lexemes.size(); i++)
	{
		outfile << tokens.at(i) << " : " << lexemes.at(i) <<endl;
	}
	cout << "Entire file was successfully read." << endl;//console message
}

};


int main()
{
	//inputting names of data files
	string sourceCodeName;
	cout << "Enter the name of the source code file: ";
	cin >> sourceCodeName;
	ifstream sourceCode(sourceCodeName);

	string lexemeDataFileName;
	cout << "Enter the name of the lexeme data file: ";
	cin >> lexemeDataFileName;
	ifstream lexemeData(lexemeDataFileName);

	string outputFileName;
	cout << "Enter the name of the output file: ";
	cin >> outputFileName;
	ofstream output(outputFileName);

	//execute the words!
	LexAnalyzer lexAnalyzer(lexemeData);
	lexAnalyzer.scanFile(sourceCode, output);
	return 0;
}


