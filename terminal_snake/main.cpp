#include <iostream>
#include <algorithm>
#include <windows.h>

#include "game.h"
#include "mode.h"
#include "menu.h"

std::pair<int, int> getWindowSizes() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &csbi
    );

    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return { width, height };
}

int main() {
    Menu menu;
    Game game;
    Mode mode = MENU;

    while (mode != EXIT) {
        switch (mode) {
        case MENU: 
            mode = menu.launchMenu(getWindowSizes);
            break;
        case GAME:
            mode = game.launchGame(getWindowSizes);
            break;
        }
    }

    return 0;
}