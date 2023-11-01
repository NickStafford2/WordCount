// testing the implementation of class WordList
// 9/04/2015

#include <iostream>
#include <string>
#include "WordList.h" // class definitions

using std::cout; using std::endl;

void testfunc(WordList); // function to test pass-by-value for WordList class

int main() {

	WordList w;

	// testing regular member functions
	w.addWord("one");
	w.addWord("one"); // adding duplicate
	w.addWord("two");
	w.addWord("three");

	cout << "word list is:\n";
	w.print();

	WordList w2, w3;

	w3 = w2 = w; // testing stacked overloaded assignment

	w2.print();
	w3.print();

	w3 = w3; // testing protection against self-assingment

	if (equal(w2, w3))
		cout << "w2 is equal to w3" << endl;
	else
		cout << "w2 is not equal to w3" << endl;

	testfunc(w); // testing copy constructor
	w.print(); // if destructor is implemented correctly
	// this should print properly after testfunc completes
}



void testfunc(WordList myList) { // copy constructor is invoked on "myList"
	myList.print();
} // destructor is invoked when "myList" goes out of scope
