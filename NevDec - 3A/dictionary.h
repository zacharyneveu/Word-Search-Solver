
///Zachary Neveu | neveu.z@husky.neu.edu
//Jake Dec | dec.j@husky.neu.edu
//
//This file includes: Definition of the dictionary class used for reading a list
//of words from a dictionary file and storing them in a vector.
//

//Includes
#include<iostream>
#include<string>
#include<vector>

//standard namespace
using namespace std;

class dictionary
{
private:
	vector<string> dict;
public:
	//constructor
	dictionary() {}

	//read function reads from file into the dictionary vector
	void read(string filepath);

	//Sort function sorts words in dictionary vector using selectionsort
	void slectionSort();

	//lookup function uses binary search to determine if a word is in the
	//dictionary, using binary search
	bool lookup(string query);

	//overloaded << operator prints the word list
	friend ostream& operator<< (ostream& ostr, const dictionary &dictionary);

	//return the dictionary
	vector<string> getDictionary() const;
};