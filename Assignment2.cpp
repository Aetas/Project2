//
// Derek Prince
// CSCI 2270 Assignment 2
// Hemingway's 350 stalkers
//
//

#include<iostream>
//#include<cstdlib>
#include<string>
#include<fstream>

using std::endl;
using std::cin;
using std::cout;
using std::string;

struct wordbank
{
	string word;
	int count = 0;
};

struct blacklist	//because why not, now i have a constructor
{
	blacklist();
	string list[50];
};

void pull(std::ifstream &in_doc, wordbank *bank[]);
void double_array(wordbank *bank[]);
void commit(wordbank *bank[], string &buffer, int top);
bool if_commons(string &buffer, wordbank *bank[]);

blacklist nay;		//nay tarry 'bout these words. or that there are 50 global strings floating about.
int size = 100;		//for doubling and book keeping
int doubled = 0;	//how many times doubled
int made = 0;

int main()
{
	string document;	//doc-to-be
	int print_num;	//number of top words to print
//	cin >> document >> print_num;
	//cin >> print_num;
	print_num = 10;

	std::ifstream in_doc;	//make ifstream
	in_doc.open("Hemingway_edit.txt"/*document*/);	//open file

	wordbank *bank = new wordbank[size];	//start with the initial 100.
	
	if (in_doc.is_open())	//check if it opened successfully
	{
		pull(in_doc, &bank);	//pull words
		in_doc.close();	//close doc after done
	}
	else	//otherwise it didnt open
	{
		while (!in_doc.is_open())	//query reoeatedly until file is found.
		{
			cout << "\n Document not found"
				<< "\n <name.txt>: ";
			getline(cin, document);
			in_doc.open(document);	//open again to update contitions
		}
		pull(in_doc, &bank);				//pull words
		in_doc.close();		//close after end
	}

	//print stuff.
	for (int i = 0; i < print_num; i++)
	{
		cout << bank[i].count << " - " << bank[i].word << endl;
		cout << "#" << endl;
	}
	cout << "Array doubled: " << doubled << endl;
	cout << "#" << endl;
	cout << "Unique non-common words: " << made << endl;

	cout << endl
		<< endl;
	return 0;
}

void pull(std::ifstream &in_doc, wordbank *bank[])	//grab words.
{
	string buffer;
	int position = 0;
	while (getline(in_doc, buffer, ' '))
	{
		if (if_commons(buffer, bank))
		{/*nothing*/}
		else
		{
			commit(bank, buffer, made);
			made++;
		}
		if (made == size - 1)
		{
			double_array(bank); 
			doubled++;
		}
	}

}

void double_array(wordbank *bank[])	//doubles
{
	wordbank* temp = new wordbank[size*2];
	for (int i = 0; i < size; i++)
	{
		temp[i].word = bank[i]->word;
		temp[i].count = bank[i]->count;
	}
	size *= 2;
	//delete[]bank;
	*bank = temp;
	//delete[]temp;	//not sure if this is needed.
}

bool if_commons(string &buffer, wordbank *bank[])
{
	for (int i = 0; i < size; i++)
	{
		if (buffer.compare(bank[i]->word) == 0)
			return true;
	}
	return false;
}

void commit(wordbank *bank[], string &buffer, int top)
{
	bool flag = false;
	for (int i = 0; i < top; i++)
	{
		if (buffer.compare(bank[i]->word) == 0)
		{
			bank[i]->count++;
			flag = true;
		}
	}
	if (flag == false)
	{
		bank[top]->word = buffer;
		bank[top]->count++;
	}
}

blacklist::blacklist()	//Not a very pleasant way, but I have to start somewhere and this was easy. Also yay constructors.
{
	list[0] = "the";
	list[1] = "be";
	list[2] = "to";
	list[3] = "of";
	list[4] = "and";
	list[5] = "a";
	list[6] = "in";
	list[7] = "that";
	list[8] = "have";
	list[9] = "i";
	list[10] = "it";
	list[11] = "for";
	list[12] = "not";
	list[13] = "on";
	list[14] = "with";
	list[15] = "he";
	list[16] = "as";
	list[17] = "you";
	list[18] = "do";
	list[19] = "at";
	list[20] = "this";
	list[21] = "but";
	list[22] = "his";
	list[23] = "by";
	list[24] = "from";
	list[25] = "they";
	list[26] = "we";
	list[27] = "say";
	list[28] = "her";
	list[29] = "she";
	list[30] = "or";
	list[31] = "an";
	list[32] = "will";
	list[33] = "my";
	list[34] = "one";
	list[35] = "all";
	list[36] = "would";
	list[37] = "there";
	list[38] = "their";
	list[39] = "what";
	list[40] = "so";
	list[41] = "up";
	list[42] = "out";
	list[43] = "if";
	list[44] = "about";
	list[45] = "who";
	list[46] = "get";
	list[47] = "which";
	list[48] = "go";
	list[49] = "me";
}
