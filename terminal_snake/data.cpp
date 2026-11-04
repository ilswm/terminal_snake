#include "data.h"

void Data::writeResults(int score) {
    std::ofstream file("results.txt", std::ios::app);

    if (!file.is_open()) {
        return;
    }

    std::time_t now = std::time(nullptr);
    std::tm localTime{};

    localtime_s(&localTime, &now);

    file << score << "|"
        << std::put_time(&localTime, "%d.%m.%Y %H:%M")
        << '\n';
}

std::string Data::readPreviousResult() {
    std::ifstream file("results.txt");

    if (!file.is_open()) {
        return "No previous results";
    }

    std::string line;
    std::string lastLine;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            lastLine = line;
        }
    }

    if (lastLine.empty()) {
        return "No previous results";
    }

    std::stringstream ss(lastLine);

    std::string score;
    std::string date;

    if (std::getline(ss, score, '|') &&
        std::getline(ss, date)) {
        return "Previous score: " + score + " | " + date;
    }

    return "Failed to read previous result";
}