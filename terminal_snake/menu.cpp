#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

#include "menu.h"

void Menu::paint_startGame(std::pair<int, int> windowSizes, int selected) {
    using namespace std;

    const string startGame = "START GAME";
    const string quit = "QUIT";

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD position = { 0, 0 };
    SetConsoleCursorPosition(console, position);

    int width = windowSizes.first;
    int height = windowSizes.second;

    int startX = (width - static_cast<int>(startGame.size())) / 2;
    int quitX = (width - static_cast<int>(quit.size())) / 2;

    int startY = height / 2;
    int quitY = startY + 1;

    Data data;
    const std::string previousScore = data.readPreviousResult();

    int startPrevScoreX = (width - static_cast<int>(previousScore.size())) / 2;


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // START GAME
            if (i == startY &&
                j >= startX &&
                j < startX + static_cast<int>(startGame.size())) {

                if (selected == 0) {
                    SetConsoleTextAttribute(console, 14);
                }
                else {
                    SetConsoleTextAttribute(console, 7);
                }

                std::cout << startGame[j - startX];
            }

            // QUIT
            else if (i == quitY &&
                j >= quitX &&
                j < quitX + static_cast<int>(quit.size())) {

                if (selected == 1) {
                    SetConsoleTextAttribute(console, 14);
                }
                else {
                    SetConsoleTextAttribute(console, 7);
                }

                std::cout << quit[j - quitX];
            }

            else {
                SetConsoleTextAttribute(console, 7);
                std::cout << ' ';
            }
        }

        std::cout << '\n';
    }


    int prevScoreY = height + 1;

    COORD prevPosition = {
        static_cast<SHORT>(max(0, startPrevScoreX)),
        static_cast<SHORT>(prevScoreY)
    };

    SetConsoleCursorPosition(console, prevPosition);
    SetConsoleTextAttribute(console, 11);

    cout << previousScore;
    SetConsoleTextAttribute(console, 7);
}


Mode Menu::launchMenu(std::function<std::pair<int, int>()> getWindowSizes) {
    int selected = 0;

    auto windowSizes = getWindowSizes();

    system("cls");
    paint_startGame(windowSizes, selected);

    while (true) {
        int key = _getch();

        if (key == 224 || key == 0) {
            key = _getch();

            if (key == 72 || key == 'w' || key == 'ц') {
                // Up arrow
                selected = (selected - 1 + 2) % 2;
            }
            else if (key == 80 || key == 's' || key == 'ы') {
                // Down arrow
                selected = (selected + 1) % 2;
            }
            else {
                continue;
            }

            windowSizes = getWindowSizes();

            system("cls");
            paint_startGame(windowSizes, selected);
        }
        else if (key == 13) {
            // Enter
            if (selected == 0) {
                return GAME;
            }
            else {
                return EXIT;
            }
        }
    }
}