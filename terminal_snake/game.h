#pragma once

#include <utility>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <functional>

#include "direction.h"
#include "menu.h"
#include "data.h"

using Point = std::pair<int, int>;


class Game {
private:
	std::pair<int, int> snakeCoords;
	std::pair<int, int> appleCords;
public:
	Mode launchGame(std::function<std::pair<int, int>()> getWindowSizes);
	void paint(std::pair<int, int> windowSizes, Point& appleCords, std::vector<Point>& snakeCords, Direction direction);
	void moveSnake(std::vector<Point>& snakeCords, Direction dir);
	void addSnakeLength(std::vector<Point>& snakeCords, Direction dir);
	
	Direction checkDirection(Direction curDir);

	Point generateRandomPoint(int x, int y);
};

