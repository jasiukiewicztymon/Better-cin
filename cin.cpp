#include "main.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

#include <conio.h>
#include <stdio.h>
#include <Windows.h>

void bcin(std::string& output) {
	char ch = ' ';

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(h, &cbsi);
    COORD pos = cbsi.dwCursorPosition;

    COORD screen;

    std::string input = " ", newinput;
    std::vector<std::string> splitInput;
    int X = pos.X, Y = pos.Y, minX = pos.X, maxX = pos.X, index = X - minX + 1, wordindex = 0;
    screen.Y = Y;
    bool backspace = false, del = false, left = false, right = false, tab = false;

	do {
        int key;
        if (_kbhit()) {
            key = _getch();
            if (key == 224) {
                do {
                    key = _getch();
                } while (key == 224);
                if (key == 75) {
                    left = true;
                }
                else if (key == 77) {
                    right = true;
                }
                else if (key == 83) {
                    del = true;
                }
            }
            else {
                ch = key;
                if (ch == 8) {
                    backspace = true;
                }
                else if (ch == 9) {
                    tab = true;
                }
                else {
                    if (ch != 13) {
                        std::string tempch = "";
                        tempch += ch;
                        input.insert(index, tempch);
                        index++;
                        maxX++;
                    }
                }
            }
            screen.X = minX;
            SetConsoleCursorPosition(h, screen);

            std::stringstream ss(input);
            std::string tempstr;
            while (ss >> tempstr) {
                splitInput.emplace_back(tempstr);
            }

            for (int i = 0; i < splitInput.size(); i++) {
                for (int j = 0; j < splitInput[i].size() + 1; j++)
                    std::cout << " ";
            }

            if (backspace) {
                if (index > minX + 1) {
                    input.erase(index - 1, 1);
                    index--;
                    maxX--;
                }
                backspace = false;
            }
            else if (del) {
                if (index < maxX + 1) {
                    input.erase(index, 1);
                    maxX--;
                }
                del = false;
            }
            else if (left) {
                if (index > minX + 1) {
                    index--;
                }
                left = false;
            }
            else if (right) {
                if (index < maxX + 1) {
                    index++;
                }
                right = false;
            }

            screen.X = minX;
            SetConsoleCursorPosition(h, screen);

            std::cout << input;

            screen.X = index;
            SetConsoleCursorPosition(h, screen);
        }
        splitInput.clear();
	} while (ch != 13);
}
