//
// Derek Prince
// CSCI 2270 Assignment 2
// Hemingway's 350 stalkers
//
//

#include<iostream>
#include<cstdlib>
#include<string>
#include<sstream>
#include<fstream>

/*
 create blaclist string blacklist[100] to step through and check?
probably have to.
*/

using std::endl;
using std::cin;
using std::cout;
using std::string;

//string blacklist[51];	//global for now -> I'll have to see where the program goes from there.
void define_blacklist(string *blacklist[]);
void pull();
void fetch_document(string &document);

struct wordbank
{
	string word;
	size_t count;
};

int main()
{
	string document;	//doc-to-be
	size_t print_num;	//number of top words to print
	fetch_document(document);
	cin >> print_num;

	std::ifstream in_doc;	//make ifstream
	in_doc.open(document);	//open file

	string *blacklist = new string[50];	//create the blacklist on a ptr so I dont have to reinitialize 50 strings in the blacklist function
	//string blacklist[50];
	define_blacklist(&blacklist);	//put in the 50 ignore words
	
	if (in_doc.is_open())	//check if it opened successfully
	{
		pull();	//pull words
		in_doc.close();	//close doc after done
	}
	else	//otherwise it didnt open
	{
		while (!in_doc.is_open())	//query reoeatedly until file is found.
		{
			cout << "\n Document not found"
				<< "\n <name.txt>: ";
			getline(cin, document, ' ');
			in_doc.open(document);	//open again to update contitions
		}
		pull();				//pull words
		in_doc.close();		//close after end
	}

	cout << endl
		<< endl;
	return 0;
}

void fetch_document(string &document)
{
	getline(cin, document, ' ');
}


void define_blacklist(string *blacklist[])	//Not a very pleasant way, but I have to start somewhere and this was easy.
{
	*blacklist[0] = "the";
	*blacklist[1] = "be";
	*blacklist[2] = "to";
	*blacklist[3] = "of";
	*blacklist[4] = "and";
	*blacklist[5] = "a";
	*blacklist[6] = "in";
	*blacklist[7] = "that";
	*blacklist[8] = "have";
	*blacklist[9] = "i";
	*blacklist[10] = "it";
	*blacklist[11] = "for";
	*blacklist[12] = "not";
	*blacklist[13] = "on";
	*blacklist[14] = "with";
	*blacklist[15] = "he";
	*blacklist[16] = "as";
	*blacklist[17] = "you";
	*blacklist[18] = "do";
	*blacklist[19] = "at";
	*blacklist[20] = "this";
	*blacklist[21] = "but";
	*blacklist[22] = "his";
	*blacklist[23] = "by";
	*blacklist[24] = "from";
	*blacklist[25] = "they";
	*blacklist[26] = "we";
	*blacklist[27] = "say";
	*blacklist[28] = "her";
	*blacklist[29] = "she";
	*blacklist[30] = "or";
	*blacklist[31] = "an";
	*blacklist[32] = "will";
	*blacklist[33] = "my";
	*blacklist[34] = "one";
	*blacklist[35] = "all";
	*blacklist[36] = "would";
	*blacklist[37] = "there";
	*blacklist[38] = "their";
	*blacklist[39] = "what";
	*blacklist[40] = "so";
	*blacklist[41] = "up";
	*blacklist[42] = "out";
	*blacklist[43] = "if";
	*blacklist[44] = "about";
	*blacklist[45] = "who";
	*blacklist[46] = "get";
	*blacklist[47] = "which";
	*blacklist[48] = "go";
	*blacklist[49] = "me";
}
