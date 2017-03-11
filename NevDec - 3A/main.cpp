//Zachary Neveu | neveu.z@husky.neu.edu
//Jake Dec | dec.j@husky.neu.edu
//
//This file includes: Main function for the word search algorithm containing
//global functions findMatches(), search(), and their respective supporting
//functions.
//

//Includes
#include<iostream>
#include<vector>
#include"d_matrix.h"
#include<string>
#include"grid.h"
#include"dictionary.h"

#define MINLENGTH 5 //Minimum length of words

//Standard Name Space
using namespace std; //standard name space

void findMatches(const dictionary &list, const grid &matrix);
void search();
int mod(int a, int b);
void searchGrid(const dictionary &d, const grid &matrix, int row, int col,
                int modx, int mody);
int shift(const int &base, const int &shift, const int &maxSize);

//Main function
int main()
{

    search();

    //system pause to keep visual studio terminal open
    system("pause");
    return 0;
}


//the search function searches the grid and finds all words in the grid
void findMatches(const dictionary &d, const grid &matrix)
{
    string currWord;
    int rows = matrix.getGrid().rows();
    int cols = matrix.getGrid().cols();

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            //search the current grid square in all 8 directions
            searchGrid(d, matrix, row, col, 1, 0);
            searchGrid(d, matrix, row, col, 1, 1);
            searchGrid(d, matrix, row, col, -1, 0);
            searchGrid(d, matrix, row, col, -1, -1);
            searchGrid(d, matrix, row, col, 0, 1);
            searchGrid(d, matrix, row, col, 0, -1);
            searchGrid(d, matrix, row, col, 1, -1);
            searchGrid(d, matrix, row, col, -1, 1);
        }
    }
}//End function

//findMatches function uses the search function to match words in the dictionary
//with words found in the grid and prints all found matches
void search()
{
    //Get grid name from user
    string gridName;
    cout << "Enter the file name of the word grid: ";
    cin >> gridName;
    grid g(gridName);

    //use hard-coded dictionary
    dictionary d;
    d.read("sortedDictionary.txt");
    //if using something other than the sorted dictionary, sort it
    //d.selectionSort();
    findMatches(d, g);
}//End function

//searches an x,y position in the grid (row, col) in a given direction, given
//by modx, mody will create a query string and search each against the
//dictionary until it wraps around, or the query substring is not found
//in the dictionary.
void searchGrid(const dictionary &d, const grid &matrix, int row, int col,
                int modx, int mody)
{
    string query = "";
    int index;
    const int initialRow = row;
    const int initialCol = col;
    int size = matrix.getGrid().rows();

    //build the minimum size word
    while (query.length() < MINLENGTH)
    {
        query += matrix.getGrid()[row][col];
        row = shift(row, modx, size);
        col = shift(col, mody, size);
    }

    //while the query length is less than the maximum query size
    while (query.length() <= size)
    {
        //do the binary search and switch over the enum result
        switch (d.improvedBinarySearch(query, index))
        {
        //If found, print out the word and information.
        case FOUND:
            printf("Word: %s Row: %d Col: %d Index: %d\n",
                   query.c_str(), initialRow, initialCol, index);

        //fall through
        //If found or not found, add the next letter to the query
        case NOT_FOUND:
            query += matrix.getGrid()[row][col];
            row = shift(row, modx, size);
            col = shift(col, mody, size);
            break;

        //the query string is not a substring of any item in the dictionary,
        //end search in this direction.
        case NO_SUBSTRING:
            return;

        default:
            //cant reach
            return;
        }
    }

    return;
}

//shifts the row or column by a factor, if it goes above the maxSize or below
//zero shift accordingly. Does not use the mod operator (slightly faster)
int shift(const int &base, const int &shift, const int &maxSize)
{
    //shift the base number
    int result = base + shift;

    //if it falls out of the array range, loop around to other side of array
    if (result < 0)
    {
        result += maxSize;
    }
    else if (result == maxSize)
    {
        result -= maxSize;
    }

    return result;
}
