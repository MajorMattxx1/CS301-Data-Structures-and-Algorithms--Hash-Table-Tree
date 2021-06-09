// Defines the entry point for the console application.
//

#include "DictTree.h"
#include "HashTable.h"
#include<string>
#include<iostream>
using namespace std;

void display1(string& anItem)
{
	cout << "Displaying item - " << anItem << endl;
}

void display2(int& anItem)
{
	cout << "Displaying item - " << anItem << endl;
}

void TreeTest1(DictTree<int, string>* testTable)
{
	testTable->add(60, "F");
	testTable->add(70, "G");
	testTable->add(40, "D");
	testTable->add(80, "H");
	testTable->add(30, "C");
	testTable->add(50, "E");
	testTable->add(10, "A");
	testTable->add(20, "B");

	cout << "Traversing data items:\n";
	testTable->traverse(display1);

	testTable->remove(10);  // A
	testTable->remove(80);	// H
	testTable->remove(40);	// D

	cout << "\nAfter Removing 10/A, 40/D & 80/H, traverse data items:\n";
	testTable->traverse(display1);

	cout << "\nTrying to remove 40/D again\n";
	if (testTable->remove(40))
		cout << "Removed second 40 :-(\n\n";
	else
		cout << "Could not remove second 40 :-)\n\n";

	

	cout << "Getting key/item 20/B: " << testTable->getItem(20) << endl;

	cout << "Getting key/item 70/G: " << testTable->getItem(70) << endl;

	cout << "Getting key/item 50/E: " << testTable->getItem(50) << endl;

	cout << "Contains key/item 80/H: " << testTable->contains(80) << endl;

	cout << "Contains key/item 00/??: " << testTable->contains(00) << endl;


	cout << "\nAfter changing 10/A to 10/Z, traverse data items:\n";
	testTable->add(10, "Z");
	testTable->traverse(display1);
}

void HashTest1(HashTable<int, string>* testTable)
{
	testTable->add(60, "F");
	testTable->add(70, "G");
	testTable->add(40, "D");
	testTable->add(80, "H");
	testTable->add(30, "C");
	testTable->add(50, "E");
	testTable->add(10, "A");
	testTable->add(20, "B");

	cout << "Traversing data items:\n";
	testTable->traverse(display1);

	testTable->remove(10);
	testTable->remove(80);
	testTable->remove(40);

	cout << "\nAfter Removing 10/A, 40/D & 80/H, traverse data items:\n";
	testTable->traverse(display1);

	cout << "\nTrying to remove 40/D again\n";
	if (testTable->remove(40))
		cout << "Removed second 40 :-(\n\n";
	else
		cout << "Could not remove second 40 :-)\n\n";

	cout << "Getting key/item 20/B: " << testTable->getItem(20) << endl;

	cout << "Getting key/item 70/G: " << testTable->getItem(70) << endl;

	cout << "Getting key/item 50/E: " << testTable->getItem(50) << endl;

	cout << "Contains key/item 80/H: " << testTable->contains(80) << endl;

	cout << "Contains key/item 00/??: " << testTable->contains(00) << endl;

	//testTable->clear();

	cout << "\nTrying to traverse after clear\n";
	//testTable->traverse(display1);
	cout << "If nothing displayed, that is good!\n";

	if (testTable->remove(20))
		cout << "Removed 20 from an empty dictionary :-(\n\n";
	else
		cout << "Could not remove 20 from an empty dictionary :-)\n\n";
}

int main()
{
	cout << "Testing DictTree" << endl << endl;
	DictTree<int, string>* tree1 = new DictTree<int, string>();
//	cout << "-----------------------------------------" << endl;
//	cout << "Testing HashTree" << endl << endl;
//	HashTable<int, string>* dict1 = new HashTable<int, string>();

	TreeTest1(tree1);
//	HashTest1(dict1);

    return 0;
}