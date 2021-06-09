// TreeTemplateIter_F2019.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "TreeT.h"
using namespace std;

// Used with traverse to print out all the elements in traverse
void PrintInt(int& elem) {
	std::cout << elem << "\n";
}

int main()
{
	TreeT<int> myTree;

	myTree.Add(5);
	myTree.Add(3);
	myTree.Add(12);
	myTree.Add(7);
	myTree.Add(2);
	myTree.Add(4);
	myTree.Add(10);
	myTree.Add(9);
	myTree.Add(6);
	myTree.Add(16);
	myTree.Add(8);
	myTree.Add(11);

	cout << "Before:" << endl;
	cout << "Length: " << myTree.Size() << endl;
	myTree.Traverse(PrintInt);		// Pass in the PrintInt function (see above main)
	myTree.Remove(7);
	cout << "After:" << endl;
	cout << "Length: " << myTree.Size() << endl;
	myTree.Traverse(PrintInt);

    return 0;
}
