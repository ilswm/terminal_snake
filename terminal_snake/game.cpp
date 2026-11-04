#include "game.h"

void Game::moveSnake(std::vector<std::pair<int, int>>& snakeCords, Direction dir) {
	for (int i = static_cast<int>(snakeCords.size()) - 1; i > 0; i--) {
		snakeCords[i] = snakeCords[i - 1];
	}

	switch (dir) {
	case DIR_UP:
		snakeCords[0].second--;
		break;
	case DIR_DOWN:
		snakeCords[0].second++;
		break;
	case DIR_LEFT:
		snakeCords[0].first--;
		break;
	case DIR_RIGHT:
		snakeCords[0].first++;
		break;
	}
}

// Tracking pressing on keyboard
Direction Game::checkDirection(Direction curDir) {
	if (_kbhit()) {
		char key = _getch();
		if ((key == 'w') && curDir != DIR_DOWN) return DIR_UP;
		else if ((key == 'a') && curDir != DIR_RIGHT) return DIR_LEFT;
		else if ((key == 'd') && curDir != DIR_LEFT) return DIR_RIGHT;
		else if ((key == 's') && curDir != DIR_UP) return DIR_DOWN;
	}
	return curDir;
}

void Game::paint(std::pair<int, int> windowSizes, Point& appleCords, std::vector<Point>& snakeCords, Direction direction) {
	using namespace std;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { 0,0 };
	SetConsoleCursorPosition(console, position);

	string score = " SCORE: " + to_string(snakeCords.size()) + " ";
	int scoreStart = (windowSizes.first - score.size()) / 2;

	for (int i = 0; i < windowSizes.second; i++) {
		for (int j = 0; j < windowSizes.first; j++) {
			// Print score
			if (i == 1 && j >= scoreStart && j < scoreStart + score.size()) {
				cout << score[j - scoreStart];
			}
			else if (j <= 1 || j >= windowSizes.first - 2 || i <= 2 || i >= windowSizes.second - 2) cout << "#";
			else if (snakeCords[0] == make_pair(j, i)) {
				cout << "O";
			}
			else if (find(snakeCords.begin() + 1, snakeCords.end(), make_pair(j, i)) != snakeCords.end()) {
				cout << "o";
			}
			else if (appleCords.first == j && appleCords.second == i) cout << "*";
			else cout << " ";
		}
	}
}

// Add length to snake
void Game::addSnakeLength(std::vector<Point>& snakeCords, Direction dir) {
	snakeCords.push_back(snakeCords.back());

	for (std::size_t i = snakeCords.size() - 1; i > 0; --i) {
		snakeCords[i] = snakeCords[i - 1];
	}

	switch (dir) {
	case DIR_UP:
		snakeCords[0].second--;
		break;
	case DIR_DOWN:
		snakeCords[0].second++;
		break;
	case DIR_LEFT:
		snakeCords[0].first--;
		break;
	case DIR_RIGHT:
		snakeCords[0].first++;
		break;
	}
}

// Generate radnom point on plane
Point Game::generateRandomPoint(int x, int y) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> distX(2, x - 3);
	std::uniform_int_distribution<int> distY(2, y - 4);

	return { distX(gen), distY(gen) };
}

// Starting function of game
Mode Game::launchGame(std::function<std::pair<int, int>()> getWindowSizes) {
	auto sizes = getWindowSizes();
	Point appleCords = generateRandomPoint(sizes.first, sizes.second);;
	std::vector<Point> snakeCords;

	Direction direction = DIR_UP;
	bool flag = true;

	snakeCords.push_back({ sizes.first / 2, sizes.second / 2 }); // start cords for snake

	while (flag) {
		direction = checkDirection(direction);

		sizes = getWindowSizes();

		if (snakeCords[0].first <= 1
			|| snakeCords[0].first >= sizes.first - 2
			|| snakeCords[0].second <= 1
			|| snakeCords[0].second >= sizes.second - 2)
		{
			flag = false;
		}

		if (std::find(snakeCords.begin() + 1, snakeCords.end(), snakeCords[0]) != snakeCords.end()) {
			flag = false;
		}

		if (snakeCords[0] == appleCords) {
			appleCords = generateRandomPoint(sizes.first, sizes.second);
			addSnakeLength(snakeCords, direction);
		}
		else {
			moveSnake(snakeCords, direction);
		}

		paint(sizes, appleCords, snakeCords, direction);

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	Data data;

	data.writeResults(snakeCords.size());

	return MENU;
}
