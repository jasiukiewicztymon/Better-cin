#include "main.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <cstddef>

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

    std::vector<std::vector<std::string>> templates = {{"cd", "root", "dir", "connect", "ftp"}, {"path", "user", "password", "help"}, {"-f", "-k"}};

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

            for (int i = 0; i < input.size() * 10; i++) {
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

            std::vector<std::string> labels;

            std::string del = " ";
            int start = 0;
            int end = input.find(del);
            while (end != -1) {
                labels.emplace_back(input.substr(start, end - start));
                start = end + del.size();
                end = input.find(del, start);
            }
            labels.emplace_back(input.substr(start, end - start));

            for (int i = 0; i < labels.size(); i++) {
                if (i == 0) {
                    if (index >= 0 && index < labels[i].size() - 1) {
                        wordindex = 0;
                        break;
                    }
                }
                else {
                    if (index >= labels[i].size() && index < labels[i].size() + i) {
                        wordindex = i;
                        break;
                    }
                }
            }

            for (int i = 0; i < labels.size(); i++) {
                std::cout << labels[i];
                if (i > 0 && i <= templates.size()) {
                    SetConsoleTextAttribute(h, 8);
                    for (int j = 0; j < templates[i - 1].size(); j++) {
                        if (templates[i - 1][j].rfind(labels[i], 0) == 0) {
                            std::cout << templates[i - 1][j].substr(labels[i].size(), templates[i - 1][j].size());
                            break;
                        }
                    }
                    SetConsoleTextAttribute(h, 15);
                }
                std::cout << " ";
            }

            screen.X = index;
            SetConsoleCursorPosition(h, screen);
        }
        splitInput.clear();
    } while (ch != 13);
}
