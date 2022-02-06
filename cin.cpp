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

void bcin(std::string& output, std::string prefix, std::vector<std::vector<std::string>> templates) {
    char ch = ' ';

    std::cout << prefix;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(h, &cbsi);
    COORD pos = cbsi.dwCursorPosition;

    COORD screen;

    std::string input = " ", newinput;
    std::vector<std::string> splitInput;
    int X = pos.X, Y = pos.Y, minX = X, maxX = 0, index = 1, wordindex = 0;
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

            for (int i = 0; i < input.size() * 10; i++) {
                std::cout << " ";
            }

            if (backspace) {
                if (index >= minX) {
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
                if (index >= minX) {
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

            std::vector<int> temp;
            std::vector<std::vector<int>> sizesref;

            temp.emplace_back(0);
            temp.emplace_back(labels[0].size());
            sizesref.emplace_back(temp);
            temp.clear();

            if (labels.size() > 1)
                for (int i = 1; i < labels.size() - 1; i++) {
                    temp.emplace_back(sizesref[i - 1][1] + 1);
                    temp.emplace_back(sizesref[i - 1][1] + 1 + labels[i].size());
                    sizesref.emplace_back(temp);
                    temp.clear();
                }

            temp.emplace_back(sizesref[sizesref.size() - 1][1] + 1);
            temp.emplace_back(input.size());
            sizesref.emplace_back(temp);
            temp.clear();

            int remindex = 0;

            for (int i = 0; i < labels.size(); i++) {
                std::cout << labels[i];
                if (i > 0 && i <= templates.size() && (index >= sizesref[i][0] && index <= sizesref[i][1])) {
                    if (!tab) {
                        SetConsoleTextAttribute(h, 8);
                        for (int j = 0; j < templates[i - 1].size(); j++) {
                            if (templates[i - 1][j].rfind(labels[i], 0) == 0) {
                                std::cout << templates[i - 1][j].substr(labels[i].size(), templates[i - 1][j].size());
                                break;
                            }
                        }
                        SetConsoleTextAttribute(h, 15);
                    }
                    else {
                        for (int j = 0; j < templates[i - 1].size(); j++) {
                            if (templates[i - 1][j].rfind(labels[i], 0) == 0) {
                                input.insert(sizesref[i][1], templates[i - 1][j].substr(labels[i].size(), templates[i - 1][j].size()));
                                std::cout << templates[i - 1][j].substr(labels[i].size(), templates[i - 1][j].size());
                                index += templates[i - 1][j].substr(labels[i].size(), templates[i - 1][j].size()).size();
                                maxX += templates[i - 1][j].substr(labels[i].size(), templates[i - 1][j].size()).size();
                                tab = false;
                                break;
                            }
                        }
                    }
                }
                std::cout << " ";
            }

            if (tab)
                tab = false;

            screen.X = index + prefix.size();
            SetConsoleCursorPosition(h, screen);
            sizesref.clear();
        }
        splitInput.clear();
    } while (ch != 13);
    output = input.substr(1, input.size());
    std::cout << "\n";
}
