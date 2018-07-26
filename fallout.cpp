

#include "fallout.h"

int main()
{
	size_t numWords, numRight = -1, i;
	bool EXIT = false;
    unsigned long wordLength;
    string aWord, answer;
    std::list<string> wordList;
    std::list<string>::iterator position;
    std::list<string>::iterator comp2pos;
    double aThird = 1.0/3.0, percentRight = 0;

    cout << "ENTER WORDS ONE AT A TIME (Terminate list with a period:'.')" << endl;
    
    // ** Read in List from user ** //
    cout << ">> "; cin >> aWord;			// Prompt for first word
    wordLength = aWord.size();				// Set word length for rest of program
    while( aWord != "." )					// Read in rest of words
    {
        if( aWord.size() == wordLength )
        {
            
            wordList.push_front(aWord);
        }
        else
        {
            cout << "Word length inconsistent!\n" << endl;
        }
        cout << ">> "; cin >> aWord;
    }
	
    numWords = wordList.size();		// Get the current list length for array size

	if (numWords <= 1)
		EXIT = true;

// ** Score similarity ** //
    while( !EXIT )
    {
        position = wordList.begin();   // Return iterators to top of list/top+1
        comp2pos = wordList.begin();
		comp2pos++;

        double ** simMat = new double * [numWords];		// Initialize simMat
        for( i=0; i < numWords; i++ )
            simMat[i] = new double [numWords];

        createSimArray( wordList, simMat );				// Create the similarity matrix
        double * wordScores = new double [numWords];
        for( i=0; i < numWords; i++)                        // Run averaged norms of each word
            wordScores[i] = aThird*(norm(simMat[i],0.5,numWords)+norm(simMat[i],1,numWords)+norm(simMat[i],2,numWords));

		size_t maxI = maxIndex(wordScores, numWords);
        for(i=0; i < maxI; i++)			// Iterate to highest-scoring word
            position++;

        cout << "\n" << "'" << *position << "' scored highest similarity." << endl;
    
// ** Prompt for number of correct chars ** //
        cout << "\nHow many correct characters? >> ";
        cin >> numRight;
        while( ( numRight < 0 ) && ( numRight >= wordLength ) )
        {
            cout << "Please enter an integer between 0 and " << wordLength << endl;
            cout << "How many correct characters? >> ";
            cin >> numRight;
        }percentRight = ( (double)numRight )/( (double)wordLength );
    
// ** Remove un-matching words from wordList ** //
        if( percentRight == 1 )
        {
            answer = *position;
            wordList.clear();
            EXIT = true;
        }
        else if( percentRight == 0 && numWords == 2 )
        {
            wordList.remove( *position );
            answer = wordList.front();
            wordList.clear();
            EXIT = true;
        }
        else
        {
            while( comp2pos != wordList.end() )
            {
				if (compareWords(*position, *comp2pos) != percentRight
					&& compareWords(*position, *comp2pos) != 1)
				{
					wordList.remove(*comp2pos);
					break;
				}
				else comp2pos++;
            }
            wordList.remove( *position );
            position = wordList.begin();
            if( wordList.size() == 1 )
            {
                position = wordList.begin();
				position++;
                answer = *position;
                EXIT = true;
            }
            else
            {
                cout << "\nREMAINING WORDS: " << endl << endl;
				printList(wordList);
            }
        }
        
		for(size_t ii = 0; ii < numWords; ii++)
			delete[] simMat[ii];                  // Free simMat and wordScores before going iterating back!!!
        delete wordScores;
// ** Return to "// ** Score similarity ** //" if list has more than one word left ** //
        numWords = wordList.size();		// Get the current list length for array size
        if( numWords == 0 )
            EXIT = true;
    }
    cout << "\nTHE PASSWORD IS " << answer << endl;
    return 0;
}
