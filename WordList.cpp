#include "WordList.h"
#include <iostream>

using std::cout;
using std::string;
using std::endl;

WordList::WordList() {
	size_ = 4;
	numOfWords = 0;
	wordArray_ = new WordOccurrence[size_];
}

// copy constructor
WordList::WordList(const WordList& wl) {
	size_ = wl.size_;
	numOfWords = wl.numOfWords;
	wordArray_ = new WordOccurrence[size_];

	for (int i = 0; i < numOfWords; ++i)
		wordArray_[i] = wl.wordArray_[i];
}


WordList::~WordList() {
	delete[] wordArray_;
}

void WordList::addWord(const string& word) {
	// sort words in wordarray alphabetically
	// check to see if word is in wordarray. if so increment
	for (int i = 0; i < size_; ++i) {
		if (wordArray_[i].matchWord(word)) {
			wordArray_[i].increment();
			return;
		}
	}
	// if not in wordarray, add it to the array

	// check if array is full, if so increase size of array
	if (size_ == numOfWords + 1) {
		size_ += 4;
		WordOccurrence* tempArray = new WordOccurrence[size_];
		for (int i = 0; i < numOfWords; ++i) {
			tempArray[i] = wordArray_[i];
		}
		delete[] wordArray_;
		wordArray_ = tempArray;
	}
	// find location to add word
	int insertIndex = 0;
	for (int i = 0; i < numOfWords; ++i) {
		/* the compare() functon of the string class returns the following
			- a negative number if the first nonmatching charicter in the object is < the first nonmatching charicter in the compared string
			- 0 if lhs and rhs are the same
			- a positive number if the first nonmatching charicter in the object is > the first nonmatching charicter in the compared string
		*/
		// insert the new word at the index where the new word compares larger than the word already at that index.
		if (wordArray_[i].getWord().compare(word) > 0) {  // if word is less than word at i 
			insertIndex = i; // insert word at that location
			break; // stop comparing once the location is known
		}
		else {
			insertIndex = i + 1;
		}

	}
	// shift all values > insertIndex to the next location in array
	// start at end of wordarray_ and continue until insertIndex

	for (int i = numOfWords - 1; insertIndex <= i; --i) {
		wordArray_[i + 1] = wordArray_[i];
	}

	wordArray_[insertIndex] = WordOccurrence(word, 1); // increment after so you access correct wordOccurrence
	++numOfWords;
	//cout << "insertIndex " << insertIndex << " word: "<< word << endl;
	//print();
	//cout << endl;
}

void WordList::print() {
	/*	print the words not in the order of the array, but in the order of number, then alphabetically
	*/

	// check if there is any words. if not, tell the user
	if (numOfWords == 0) {
		std::cerr << "no words found" << endl;
		return;
	}
	// display header
	cout << "# \tWORD" << endl;

	int mostFrequent = 0;
	// find how many times the most common word appears
	for (int i = 0; i < numOfWords; ++i) {
		if (wordArray_[i].getNum() > mostFrequent)
			mostFrequent = wordArray_[i].getNum();
	}
	while (mostFrequent > 0) {
		// print out all the words that appear mostFrequent number of times
		// wordArray_ is sorted, so after number, they print out alphabetically
		for (int i = 0; i < numOfWords; ++i) {
			if (wordArray_[i].getNum() == mostFrequent) //I know this is innefficent. but it is easy to understand
				cout << wordArray_[i].getNum() << "\t" << wordArray_[i].getWord() << endl;
		}
		--mostFrequent;
	}
}

WordList& WordList::operator=(const WordList& rhs) {
	// assignment operator. 
	if (this == &rhs) return *this;

	if (wordArray_ != nullptr)
		delete[] wordArray_;

	size_ = rhs.size_;
	numOfWords = rhs.numOfWords;
	wordArray_ = new WordOccurrence[size_];

	for (int i = 0; i < size_; ++i)
		wordArray_[i] = rhs.wordArray_[i];

	return *this;
}

//-----------------------------------------------------
WordOccurrence::WordOccurrence(const string& word, int num) {
	word_ = word;
	num_ = num;
}

bool WordOccurrence::matchWord(const string& s) {
	// returns true if word matches stored
	if (s == word_) return true;
	else return false;
}

void WordOccurrence::increment() {
	++num_;
}

string WordOccurrence::getWord() const {
	return word_;
}

int WordOccurrence::getNum() const {
	return num_;
}

//--------------------------------
bool equal(const WordList& lhs, const WordList& rhs) {
	// checks to see if both wordlists are exactly the same. 
	// wordlists are organized alphabetically so the index values match if they are the same
	if (lhs.numOfWords != rhs.numOfWords) return false;

	for (int i = 0; i < lhs.numOfWords; ++i) {
		// if anything is different, return false
		if (lhs.wordArray_[i].getWord() != rhs.wordArray_[i].getWord() ||
			lhs.wordArray_[i].getNum() != rhs.wordArray_[i].getNum())
			return false;
	}
	// if everything is the same, return true
	return true;
}
