/*
	Patrick Jirele
*/

#include <iostream>
#include <fstream> // for file IO
#include <typeinfo> // for typeid
#include <sstream> // for splitting strings
#include <string>
using namespace std;

// array doubles variable
int numDoubles = 0;
// number of duplicates
int numDuplicates = 0;

// must use this struct
struct wordItem
{
	string word;
	int count = 0;
};

/**
********* REQUIRED FUNCTIONS!
*/

/*
* Function name: doubleArraySize
* Purpose: accepts an array and doubles the size
* @param wordItemList - pointer to your word item array
* @param length - the length of your wordItem array
* @return - none
* Note: create a new array with double the size,
*		copy over the elements of wordItemList,
*		delete [] wordItemList,
*		reassign wordItemList to the new array
* Note: can call with doubleArraySize(wordItemList, length);
*/
void doubleArraySize(wordItem*& wordItemList, int& length)
{
	wordItem* wordArray = new wordItem[length * 2];

	for (int i = 0; i < length; i++)
	{
		wordArray[i] = wordItemList[i];
	} // end for
	delete[] wordItemList;
	wordItemList = wordArray;
	length = length * 2;
	
	numDoubles++;


} // end doubleArraySize

/*
* Function name: addWord
* Purpose: adds a new word to our list, everything is passed by ref!
* @param wordItemList - address of pointer to your word item array
* @param wordIndex - the current index in the array
* @param length - the length of your wordItem array
* @param nextWord - the word we want to add
* @return - none
* Note: handle two cases, the case where the word already
* 		has a wordItem in the array (increment count),
* 		and the case where it's not in there. In the second
* 		case we might have to double the size if wordIndex == length
* 		and add a new wordItem with count 1
*/
void addWord(wordItem*& wordItemList, int& wordIndex, int& length, string nextWord)
{
	bool found = false;

	for (int i = 0; i < wordIndex; i++)
	{
		if (wordIndex == length)
		{
			doubleArraySize(wordItemList, wordIndex);
		} // end if

		if (wordItemList[i].word == nextWord)
		{
			wordItemList[i].count = wordItemList[i].count + 1;
			found = true;
		} // end else if

		else
		{
			if (wordIndex == length)
			{
				doubleArraySize(wordItemList, wordIndex);
			} // end if

			wordItemList[i + 1].word = nextWord;

			wordItem wordArray;


			wordArray.word = nextWord;
			wordArray.count = 1;
			wordItemList[wordIndex] = wordArray;
			wordIndex++;
			found = false;
		} // end else
	} // end for
} // end addWord


/*
* Function name: arraySort
* Purpose: sort an array of wordItems, decreasing, by their count fields
* @param list - an array of wordItems to be sorted
* @param length - the length of the words array
* Note: should modify the original array but not return anything
* should be called with arraySort(wordItemList, wordIndex)
* can modify the array directly (list[0] = something)
*/
void arraySort(wordItem wordItemList[], int wordIndex)
{

	for (int i = 0; i < wordIndex; i++)
	{
		for (int j = 0; j < wordIndex; j++)
		{
			if (wordItemList[j].count < wordItemList[j + 1].count)
			{
				wordItem placeHolder;
				placeHolder = wordItemList[j];
				wordItemList[j] = wordItemList[j + 1];
				wordItemList[j + 1] = placeHolder;
			} // end if
		} // end for
	} // end for
} // end arraySort


/*
* Function name: printTopN
* Purpose: to print the top N high frequency words
* @param wordItemList - a pointer that points to a *sorted* array of
wordItems
* @param topN - the number of top frequency words to print
* @return none
*/
void printTopN(wordItem wordItemList[], int topN)
{
	arraySort(wordItemList, 2 ^ numDoubles);
	for (int i = 0; i < topN; i++)
	{
		cout << wordItemList[i].word << ", " << wordItemList[i].count << endl;
	}
} // end printTopN



/************************************************************/
/**** feel free to add any other functions you need here ****/
/************************************************************/

void printArr(wordItem wordItemList[], int wordIndex)
{
	for (int i = 0; i < wordIndex; i++)
	{
		cout << wordItemList[i].word << ", " << wordItemList[i].count << endl;
	}
}


/*
* Main function (driver)
* take care of reading in the file and creating the arrays here
*/

int main()
{
	int wordIndex = 0; // keep track of where to insert new wordItems
	int length = 1; // keep track of total size of array
	string str, position;
	wordItem* wordItemList = new wordItem[length]; // create a word item array starting with 1 spot

	// get command line arguments
	int topN = 4;
	string inputFile = "shakespeare.txt";


	// (1) parse line by line from file
	//   (1a) break up lines by spaces to get each word
	//   (1b) put each word into the array
	//        if there is already a wordItem for the word, increase the count
	// 		  if the word is not in the array, create a new wordItem with count = 1
	ifstream file(inputFile);

	while (getline(file, str))
	{
		stringstream ss(str);
		while (str.find(" ") < str.length())
		{
			position = str.substr(0, str.find(" "));

			addWord(wordItemList, wordIndex, length, position);

			str = str.substr(str.find(" ") + 1);
		} // end while

		str = str.substr(str.find(" ") + 1);
		position = str.substr(0, str.find(" "));

		addWord(wordItemList, wordIndex, length, position);
	} // end while


	// (2) sort your array of wordItems

	arraySort(wordItemList, wordIndex);
	// (3) print out the top n and their frequency

	printTopN(wordItemList, topN);
	// (4) print out number of array doubles (global variable up top for this)

	cout << numDoubles << endl;
	// (5) print out total number of unique words

	cout << wordIndex << endl;
	// (6) print out total number of duplicate words

	cout << numDuplicates << endl;

	delete[] wordItemList; // clean up
	return 0; //return "success" status
}