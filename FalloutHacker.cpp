#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	string fname = "C:\\Users\\charc\\source\\repos\\FalloutHacker\\Debug\\Passwords.txt";
	WordList myWordList(fname);

	while (myWordList.update()) {}

	return 0;
}