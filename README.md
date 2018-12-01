# Fallout-Computer-Hack-Guesser

Given a list of words, guess the 'password'. Incorrect guesses will get a number of characters 
correct, which you use to narrow down what the password is. 

This program prompts the user for a list of words, then uses similarity between 
each word from a list to guess the word that is most common to the whole list in terms of characters in each spot.

Currently, the WordList class supports the word list specification through a text file; to use, just update the file name/location in the main execution function within FalloutHacker.cpp.
