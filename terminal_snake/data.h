#pragma once

#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

class Data {
public:
    void writeResults(int score);
    std::string readPreviousResult();
};