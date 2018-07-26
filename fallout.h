#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <math.h>
//#include "LL.hpp"

using namespace std;
//***********************************************************************************************************************************
//
// double compareWords( word1, word2 )				--> Returns "percentage similar" = (no. of chars same)/(wordLength)
// double ** createSimArray( wordList )				--> Returns a (list length)by(list length) array of values from double
// compareWords( s1, s2 )                           --> Returns number of characters from s1,s2 that are the same ()
// double norm( array, p )							--> Computes the p-norm of array
// int maxIndex( array )							--> Returns the index of the largest element in array
// void printList( wordList )						--> Prints the list to stdout
//
//***********************************************************************************************************************************

// Forward declarations:
double compareWords( string word1, string word2 );
double ** createSimArray( list<string> wordList, double **simMat );
double norm(double *array, double p, int arrayLength);
int maxIndex(double * array, int arrayLength);
void printList(list<string> wordList);

double compareWords( string word1, string word2 )
{
    int i = 0;
    double percentage = 0;
    double length = 0, charcount = 0;
    
    length = word1.size();
    
    if( length != word2.size() )
    {
        cout << "OOPS! WORDS NOT SAME LENGTH!";
    }
    else
    {
        for(i=0; i<length; i++)
        {
            if( word1[i] == word2[i] )
            {
                charcount = charcount + 1;
            }
        }
    }
    
    percentage = charcount/length;
    return percentage;
}

double ** createSimArray( list<string> wordList, double **simMat )
{
    int i, j;
    if( wordList.empty() )	// Double-check to make sure not passing in an empty list
    {
        cout << "Error: passing empty word list into createSimArray!\n";
        return NULL;
    }
    else
    {
        list<string>::iterator position = wordList.begin();	// Construct list iterators to run through list
        list<string>::iterator comp2pos = wordList.begin();
        const size_t listlength = wordList.size();
        
        for( i=0; i < listlength ; i++ )
        {
            for( j=0; j < listlength ; j++ )
            {
                
                simMat[i][j] = compareWords( *position, *comp2pos );
                //cout << "simMat[" << i << "][" << j << "] = " << simMat[i][j] << endl;
                comp2pos++;
            }
            position++;
            comp2pos = wordList.begin();
        }
    }
    return simMat;
}


double norm(double *array, double p, int arrayLength)
{
    double computed = 0;
    int i = 0;
    
    for(i=0; i < arrayLength; i++)
    {
        computed = computed + pow(array[i],p);
    }
    //computed = pow(computed,1/p);
    
    return computed;
}


size_t maxIndex(double * array, size_t arrayLength)
{
    size_t i = 0, Index = 0;
    double currentGuess = 0;
    
    for( i = 0 ; i < arrayLength; i++ )
    {
        if( array[i] > currentGuess )
        {
            currentGuess = array[i];
            Index = i;
        }
    }
    
    return Index;
}

void printList(list<string> wordList)
{
	list<string>::iterator itr = wordList.begin();
	for (; itr != wordList.end(); ++itr)
		cout << *itr << endl;
}