#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "LL.hpp"

using namespace std;
//***********************************************************************************************************************************
//
// double compareWords( word1, word2 )				--> Returns "percentage similar" = (no. of chars same)/(wordLength)
// double ** createSimArray( wordList )				--> Returns a (list length)by(list length) array of values from double
// compareWords( s1, s2 )                           --> Returns number of characters from s1,s2 that are the same ()
// double norm( array, p )							--> Computes the p-norm of array
// int maxIndex( array )							--> Returns the index of the largest element in array
//
//***********************************************************************************************************************************


double compareWords( string word1, string word2 );
double ** createSimArray( List<string> wordList, double **simMat );
double norm(double *array, double p, int arrayLength);
int maxIndex(double * array, int arrayLength);


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

double ** createSimArray( List<string> wordList, double **simMat )
{
    int i, j;
    if( wordList.isEmpty() )	// Double-check to make sure not passing in an empty list
    {
        cout << "Error: passing empty word list into createSimArray!\n";
        return NULL;
    }
    else
    {
        ListItr<string> position = wordList.first();	// Construct list iterators to run through list
        ListItr<string> comp2pos = wordList.first();
        const int listlength = wordList.getListLength();
        
        for( i=0; i < listlength ; i++ )
        {
            for( j=0; j < listlength ; j++ )
            {
                
                simMat[i][j] = compareWords( position.retrieve(), comp2pos.retrieve() );
                //cout << "simMat[" << i << "][" << j << "] = " << simMat[i][j] << endl;
                comp2pos.advance();
            }
            position.advance();
            comp2pos = wordList.first();
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


int maxIndex(double * array, int arrayLength)
{
    int i = 0, Index = 0;
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