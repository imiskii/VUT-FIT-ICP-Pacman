#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <vector>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;

class Logger
{
private:
    ofstream logFile;

public:
    ~Logger();
    bool createLogFile(vector<string> &fileLines);
    void log(string msg);
};

#endif
