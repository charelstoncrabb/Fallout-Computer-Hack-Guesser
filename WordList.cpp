#include "pch.h"
#include "WordList.h"
#include <fstream>
#include <iostream>

using namespace std;

WordList::WordList(string filename) : nGuesses(N_GUESSES), wordLen(0)
{
	ifstream fs(filename, ios::in);
	if (!fs.good())
		throw std::runtime_error("Error opening word list file!");
	for (char word[100]; fs.getline(word, 100);)
		words.push_back(string(word));
	validateWordList();
}

void WordList::validateWordList()
{
	wordLen = words[0].size()-1;
	for (string w : words)
		if (w.size() != wordLen + 1)
			throw std::runtime_error("Inconsistent word lengths! All words must be the same number of characters.");
}

bool WordList::update()
{
	// Calculate all word similarity ranks:
	vector<vector<double>> simArray = calcSimArray();
	vector<double> wordRanks = calcWordRanks(simArray);
	size_t highRankInd = findTopWord(wordRanks);

	// Print words with ranks and get guess from user:
	printWords(wordRanks);
	printTopWord(wordRanks);
	size_t I = getGuess();

	// Remove all words with inequal similarity
	double similarity = (double)I / (double)wordLen;
	if ( similarity - 1.0 > -1.e-12)
		return false;
	vector<size_t> toErase = findDissimilars(words[highRankInd], simArray, similarity);
	erase(toErase);

	return --nGuesses || !words.empty();
}

WordList::~WordList()
{
}

double WordList::strsim(string a, string b)
{
	double ans = 0.;
	if (a.size() != b.size())
		throw std::runtime_error("String similarity undefined for different length strings");
	for (size_t i = 0; i < a.size(); i++)
		ans += a[i] == b[i] ? 1.0 : 0.0;

	return ans / wordLen;
}

void WordList::printWords()
{
	for (string w : words)
		cout << w << endl;
}

void WordList::printWords(vector<double> wordRanks)
{
	if (wordRanks.size() != words.size())
		throw std::runtime_error("Word/wordRanks size mismatch! word ranks should be updated.");
	cout << "Words:\tRanks:" << endl;
	for (size_t i = 0; i < words.size(); i++)
		cout << words[i] << '\t' << wordRanks[i] << endl;
}

size_t WordList::getGuess()
{
	size_t nRight;
	cout << endl << "Number correct characters: ";
	cin >> nRight;
	return nRight;
}

vector<vector<double>> WordList::calcSimArray()
{
	vector<vector<double>> simarray(words.size(), vector<double>(words.size(), 0.));
	for (size_t i = 0; i < words.size(); i++)
		for (size_t j = 0; j < words.size(); j++)
			simarray[i][j] = strsim(words[i], words[j]);
	return simarray;
}

vector<double> WordList::calcWordRanks(vector<vector<double>> simarray)
{
	int i = 0;
	vector<double> ans(simarray.size(),0.0);
	for (vector<double> simvect : simarray)
		ans[i++] = calcWordRank(simvect);
	return ans;
}

double WordList::calcWordRank(vector<double> simvect)
{
	double l_half = 0., l_1 = 0., l_2 = 0.;
	for (double d : simvect)
	{
		l_half += pow(d, 0.5);
		l_1 += d;
		l_2 += pow(d, 2.0);
	}
	return (pow(l_half, 2.0) + l_1 + pow(l_2, 0.5)) / 3.0;
}

// Returns indices of words that have unequal similarity than given (words to erase from the list)
vector<size_t> WordList::findDissimilars(string word, vector<vector<double>> simarray, double similarity)
{
	vector<size_t> ans;
	size_t wordpos = find(word);
	if (wordpos < words.size())
	{
		for (size_t i = 0; i < words.size(); i++)
			if (fabs(simarray[wordpos][i] - similarity) > 1.e-12)
				ans.push_back(i);
	}
	return ans;
}

size_t WordList::findTopWord(vector<double> wordRanks)
{
	size_t ans = 0;
	double maxsim = 0.;
	for (size_t i = 0; i < wordRanks.size(); i++)
	{
		ans = wordRanks[i] >= maxsim ? i : ans;
		maxsim = ans == i ? wordRanks[i] : maxsim;
	}
	return ans;
}

void WordList::printTopWord(vector<double> wordRanks)
{
	size_t topI = findTopWord(wordRanks);
	cout << "Top ranking word:\t" << words[topI] << endl;
}

size_t WordList::find(string str)
{
	for (size_t i = 0; i < words.size(); i++)
		if (str == words[i])
			return i;
	return UINT_MAX;
}

void WordList::erase(vector<size_t> toErase)
{
	if (!toErase.empty())
		for (int i = toErase.size()-1; i >= 0; i--)
			words.erase(words.begin()+toErase[i]);
}

