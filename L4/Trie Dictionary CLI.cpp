#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

void toLowerCase(string &str)
{
	for (int i = 0; i < str.length(); ++i)
	{
		str[i]=tolower(str[i]);
	}
}

class Node
{
	public:

		bool hasMeaning;
		string meaning;
		Node *childArr[26];

		Node()
		{
			this->hasMeaning=false;
			for (int i = 0; i < 26; ++i)
			{
				this->childArr[i]=NULL;
			}
		}

		Node* getChildWithChar(char val)
		{
			if(val < 97 || val > 122)
			{
				return NULL;
			}
			else
			{
				return this->childArr[val%97];
			}
		}

		Node** getChildAddr(char val)
		{
			if(val < 97 || val > 122)
			{
				return NULL;
			}
			else
			{
				return &(this->childArr[val%97]);
			}
		}
};


class Dictionary
{
	public:
		Node* root;

		Dictionary()
		{
			this->root = new Node();
		}

		void insert(string key,string meaning)
		{
			Node* it = this->root;
			for (int i = 0; i < key.length(); ++i)
			{
				char currChar = key.at(i);
				if (it->getChildWithChar(currChar) == NULL)
				{
					*(it->getChildAddr(currChar)) = new Node();
				}

				it = it->getChildWithChar(currChar);
			}
			it->hasMeaning = true;
			it->meaning = meaning;
		}

		string retrieveMeaning(string key)
		{
			toLowerCase(key);
			Node* it = this->root;
			for (int i = 0; it != NULL && i < key.length(); ++i)
			{
				char currChar= key.at(i);
				it = it->getChildWithChar(currChar);
			}

			if (it == NULL || it->hasMeaning == false)
			{
				return "Invalid Word";
			}
			else
			{
				return it->meaning;
			}
		}

		void getFromFile(string filename)
		{
			ifstream file;
			file.open(filename);
			if (file.is_open())
			{
				string key;
				while(getline(file,key,','))
				{
					toLowerCase(key);
					string val;
					getline(file,val);
					this->insert(key,val);
				}
				file.close();
			}
		}

};



int main(void)
{

	Dictionary* dictionary = new Dictionary();
	dictionary->getFromFile("L4_P1_input.csv");

	while(true)
	{
		cout << "Enter Word to get meaning" << endl;
		string key;
		getline(cin,key);
		cout << dictionary->retrieveMeaning(key) << endl;
		cout << endl;
	}

	return 0;
}