/* 
 * Derek Prince
 * CSCI 2270 
 * Rhonda Hoenigman
 * Assignment 2 - Hemingway's 350 stalkers
 *
*/

#include<iostream>
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

wordbank* double_array(wordbank bank[]);			//doubles the array size
void pull(std::ifstream &in_doc, wordbank bank[]);	//pulls out the data. Wound up being useless.
void commit(wordbank bank[], string &buffer);		//responsible for commiting new entries in the array and in the correct place
void sort(wordbank bank[]);							//currently just a simple shitty bubble sort. meh.
bool if_commons(string &buffer);					//basically just loop control to see if things are common words

blacklist nay;		//nay tarry 'bout these words. or that there are 50 global strings floating about.
int size = 100;		//for doubling and book keeping
int doubled = 0;	//how many times doubled
int made = 0;		//entries made
int total = 0;		//commits

int main()
{
	string document;	//doc-to-be
	int print_num;		//number of top words to print
	cin >> document >> print_num;	//simple cin will work since they are spaced correctly	

	std::ifstream in_doc;	//make ifstream
	in_doc.open(document);	//open file

	wordbank *bank = new wordbank[size];	//start with the initial 100.
	
	if (in_doc.is_open())	//check if it opened successfully
	{
		string buffer;	//simple string to work with
		while (!in_doc.eof())
		{
			in_doc >> buffer;
			if (if_commons(buffer) == true)	//if it matches, don't do anything
			{/*nothing*/
			}
			else
			{
				commit(bank, buffer);	//otherwise commit it to the array
			}
			if (made == size - 1)		//if the array is at the end, double it
			{
				bank = double_array(bank);	//double_array returns a pointer of wordbank type, so it can be used with the assignment operator
				doubled++;					//book keeping
			}
		}
		in_doc.close();		//close doc after done
	}
	else	//otherwise it didnt open
	{
		while (!in_doc.is_open())	//query reoeatedly until file is found.
		{
			cout << "\n Document not found"
			<< "\n <name.txt>: ";
			cin >> document;		//grab document -- number of lines was already stored
			in_doc.open(document);	//open again to update contitions
		}
		string buffer;	//simple string to work with
		while (in_doc >> buffer)
		{
			if (if_commons(buffer) == true)	//if it matches, don't do anything
			{/*nothing*/
			}
			else
			{
				commit(bank, buffer);	//otherwise commit it to the array
			}
			if (made == size - 1)		//if the array is at the end, double it
			{
				bank = double_array(bank);	//double_array returns a pointer of wordbank type, so it can be used with the assignment operator
				doubled++;					//book keeping
			}
		}
		in_doc.close();			//close after end
	}

	//print stuff.
	sort(bank);	//call simple sort on array
	for (int i = 0; i < print_num; i++)	//print the top entries, braked on the input
	{
		cout << bank[i].count << " - " << bank[i].word << endl;
		cout << "#" << endl;
	}
	cout << "Array doubled: " << doubled << endl;	//just some stats n stuff
	cout << "#" << endl;
	cout << "Unique non-common words: " << made << endl;
	cout << "#" << endl;
	cout << "Total non-common words: " << total << endl;

	cout << endl	//this might throw off the cog grader, we shall see
		<< endl;
	return 0;
}

void pull(std::ifstream &in_doc, wordbank bank[])	//grab words. doesn't actually work as it turns out
{
	string buffer;	//simple string to work with
	while (in_doc >> buffer)
	{
		if (if_commons(buffer) == true)	//if it matches, don't do anything
			{/*nothing*/}
		else
		{
			commit(bank, buffer);	//otherwise commit it to the array
		}
		if (made == size - 1)		//if the array is at the end, double it
		{
			bank = double_array(bank);	//double_array returns a pointer of wordbank type, so it can be used with the assignment operator
			doubled++;					//book keeping
		}
	}
}

wordbank* double_array(wordbank bank[])	//doubles the size, returning an object on pointer
{
	wordbank* temp = new wordbank[size*2];	//new temp -> twice the original size
	for (int i = 0; i < size; i++)
	{
		temp[i].word = bank[i].word;	//reassigns every value
		temp[i].count = bank[i].count;	//^^
	}
	size *= 2;	//book keeping

	return temp;	//return the ptr/object
}

bool if_commons(string &buffer)	//this is it's own function largely for readability and personal preference
{
	for (int i = 0; i < 50; i++)	//there are only 50 of them so...
	{
		if (buffer.compare(nay.list[i]) == 0)//str.compare kicks the bool only if it's false. Which is weird.
			{return true;}	//the word matches a common word
	}
	return false;			//no matches found 
}

void commit(wordbank bank[], string &buffer)
{
	bool flag = false;	//'already exists' flag
	for (int i = 0; i < made; i++)
	{
		if (buffer == bank[i].word)	//if the word is already in the array
		{
			bank[i].count++;		//up the counter
			flag = true;			//set flag to true
			break;					//break out
		}
	}
	if (flag == false)				//if no match was found...
	{
		bank[made].word = buffer;	//commit
		bank[made].count++;			//incriment counter to 1
		made++;						//book keeping
	}
	total++;	//still book keeping
}

void sort(wordbank bank[])
{
	wordbank temp;		//only need a single object to be stored
	bool flag = true;	//set a flag and make it true
	while (flag)		
	{
		flag = false;	//clear(), really
		for (int i = 0; i < made-1; i++)	//made-1 because it checks for the next entry. Which does not exist at the top
		{
			if (bank[i].count < bank[i + 1].count)	//if current is smaller than the next... swap
			{
				flag = true;						//update flag
				temp.count = bank[i].count;			//store temp variable
				temp.word = bank[i].word;			//^^
				bank[i].count = bank[i + 1].count;	//swap
				bank[i].word = bank[i + 1].word;	//^^
				bank[i + 1].count = temp.count;		//insert temp back into the array
				bank[i + 1].word = temp.word;		//^^
			}
		}
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