#include "main.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include<cstdlib>
#include <sstream>

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

char getch(char& ch) {
	while (1) {
		ch = getchar();
		if (ch >= 32 && ch <= 126) {
			exit(0);
		}
	}
	return ch;
}

std::string cin(char prefix, std::vector<std::string> keys, std::map<std::string, std::vector<std::string>> args) {
	const int MIN_BUFFOR_INDEX = 3;
	
	std::string output;
	std::vector<std::string> arr;
	char ch = 1;
	int index = 0, arrindex = 0, x, y;

	std::cout << " " << prefix << " ";

	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
	x = screenBufferInfo.dwCursorPosition.X;
	y = screenBufferInfo.dwCursorPosition.Y;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD screen;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	screen.X = MIN_BUFFOR_INDEX;
	screen.Y = y;
	SetConsoleCursorPosition(hOut, screen);

	do {
		getch(ch);
		output += ch;

		if (ch == 'a')
			system("color a");

		COORD temp = screen;

		screen.X = MIN_BUFFOR_INDEX;
		SetConsoleCursorPosition(hOut, screen);
		for (int i = 0; i < output.size() + 4; i++) {
			std::cout << " ";
		}

		screen = temp;
		SetConsoleCursorPosition(hOut, screen);

		std::cout << output;
	} while (ch != 13);

	return output;
}
