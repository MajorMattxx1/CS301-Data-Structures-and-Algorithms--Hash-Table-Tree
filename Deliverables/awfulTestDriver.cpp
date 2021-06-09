// modified version of previous assignment's test driver
// which absolutely does not work

#include "DictTree.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ofstream outFile;
	ifstream inFile;
	HashTable<int, string>* table;

	outFile.open("output.txt");
	inFile.open("test.txt");

	if (!inFile) {
		cout << "File not found!" << endl;
		exit(0);
	}

	string command;
	inFile >> command;
	while (command != "quit") {
		if (command == "add") {
			int key;
			inFile >> key;
			int num;
			inFile >> num;
			table->add(key, num);
			outFile << "Adding " << num << endl;
		}

		else if (command == "remove") {
			int num;
			inFile >> num;
			table->remove(num);
			outFile << "Removing " << num << endl;
		}

		else if (command == "contains") {
			int num;
			inFile >> num;
			bool val = table->contains(num);
			if (val == false) {
				outFile << val << " does not exist in table" << endl;
			}
			else {
				outFile << val << " exists in table" << endl;
			}
		}
		else if (command == "lookupItem") {
			int num;
			inFile >> num;
			int* val = table->lookupItem(num);
			if (val == nullptr) {
				outFile << *val << " does not exist in list" << endl;
			}
			else {
				outFile << *val << " exists in index " << num << endl;
			}
		}

		else if (command == "size") {
			outFile << "Length: " << table->size() << endl;
		}

		else if (command == "quit") {
			return 0;
		}
		inFile >> command;
	}
	return 0;
}