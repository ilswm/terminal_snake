#pragma once

#include <functional>
#include <utility>

#include "mode.h"
#include "data.h"

class Menu {
public:
    Mode launchMenu(std::function<std::pair<int, int>()> getWindowSizes);

private:
    void paint_startGame(std::pair<int, int> windowSizes, int selected);
};;