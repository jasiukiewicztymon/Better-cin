#include "main.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

/*
	1. Input the command and next search the command in the map
	2. Input the args with the help
*/

char getch(char& ch) {
	ch = _getch();
	return ch;
}

std::string cin(std::vector<std::string> keys, std::map<std::string, std::vector<std::string>> args) {
	std::string output;
	std::vector<char[256]> words;
	char ch, word[256];
	int objindex = 0, arrindex = 0;

	do {
		getch(ch);
		std::cout << ch;
	} while (true);

	return output;
}
