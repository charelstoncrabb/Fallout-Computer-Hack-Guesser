#include <string>
#include <vector>

constexpr auto N_GUESSES = 4;

using namespace std;

#pragma once
class WordList
{
public:
	WordList(string);
	~WordList();
	void printWords();
	bool update();

private:
	void validateWordList();
	vector<vector<double>> calcSimArray();
	vector<double> calcWordRanks(vector<vector<double>>);
	double calcWordRank(vector<double>);
	size_t findTopWord(vector<double>);
	void printTopWord(vector<double>);
	void printWords(vector<double>);
	size_t getGuess();
	vector<size_t> findDissimilars(string,vector<vector<double>>,double);
	size_t find(string);
	void erase(vector<size_t>);
	double strsim(string,string);

	size_t wordLen;
	vector<string> words;
	int nGuesses;
};

