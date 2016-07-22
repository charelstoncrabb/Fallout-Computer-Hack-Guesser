

#include "fallout.h"

int main()
{
    int numWords, numRight = -1, i, EXIT = 0;
    unsigned long wordLength;
    string aWord, answer;
    List<string> wordList;
    ListItr<string> position = wordList.zeroth();
    ListItr<string> comp2pos = wordList.zeroth();
    double aThird = 1.0/3.0, percentRight = 0;
    //ifstream file;
    //file.open("words.txt");
    cout << "ENTER WORDS ONE AT A TIME (Terminate list with a period:'.')" << endl;
    
    // ** Read in List from user ** //
    cout << ">> "; cin >> aWord;			// Prompt for first word
    //getline(file, aWord);
    //cout << aWord << endl;
    wordLength = aWord.size();				// Set word length for rest of program
    wordList.insert( aWord, position );		// Push first word to list
    while( aWord != "." )					// Read in rest of words
    {
        if( aWord.size() == wordLength )
        {
            
            wordList.insert( aWord, position );
        }
        else
        {
            cout << "Word length inconsistent!\n" << endl;
        }
        cout << ">> "; cin >> aWord;
        //getline(file, aWord);
        //cout << aWord << endl;
    }
    
    numWords = wordList.getListLength();		// Get the current list length for array size
// ** Score similarity ** //
    while( !EXIT )
    {
        position = wordList.zeroth();   // Return iterators to top of list
        comp2pos = wordList.first();
        //cout << "Numer of words = " << numWords << endl;
        double ** simMat = new double * [numWords];		// Initialize simMat
        for( i=0; i < numWords; i++ )
        {
            simMat[i] = new double [numWords];
        }
        createSimArray( wordList, simMat );				// Create the similarity matrix
        double * wordScores;
        wordScores = new (nothrow) double [numWords];
        for( i=0; i < numWords; i++)                        // Run averaged norms of each word
        {
            wordScores[i] = aThird*(norm(simMat[i],0.5,numWords)+norm(simMat[i],1,numWords)+norm(simMat[i],2,numWords));
            //cout << "Wordscore[" << i << "] = " << wordScores[i] << endl;
        }
        //cout << "Max index = " << maxIndex(wordScores, numWords) << endl;
        for(i=0; i <= maxIndex(wordScores, numWords); i++)			// Iterate to highest-scoring word
        {
            position.advance();
        }
        cout << "\n" << "'" << position.retrieve() << "' scored highest similarity." << endl;
    
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
            answer = position.retrieve();
            wordList.makeEmpty();
            EXIT = 1;
        }
        else if( percentRight == 0 && numWords == 2 )
        {
            wordList.remove( position.retrieve() );
            answer = (wordList.first()).retrieve();
            wordList.makeEmpty();
            EXIT = 1;
        }
        else
        {
            while( !comp2pos.isPastEnd() )
            {
                if( compareWords( position.retrieve(), comp2pos.retrieve() ) != percentRight 
                    && compareWords( position.retrieve(), comp2pos.retrieve() ) != 1 )
                    wordList.remove( comp2pos.retrieve() );
                comp2pos.advance();
            }
            wordList.remove( position.retrieve() );
            position = wordList.zeroth();
            if( wordList.getListLength() == 1 )
            {
                position = wordList.first();
                answer = position.retrieve();
                EXIT = 1;
            }
            else
            {
                cout << "\nREMAINING WORDS: " << endl << endl;
                wordList.printList();
            }
        }
        
        delete simMat;                  // Free simMat and wordScores before going iterating back!!!
        delete wordScores;
// ** Return to "// ** Score similarity ** //" if list has more than one word left ** //
        numWords = wordList.getListLength();		// Get the current list length for array size
        if( numWords == 0 )
            EXIT = 1;
    }
    cout << "\nTHE PASSWORD IS " << answer << endl;
    return 0;
}
