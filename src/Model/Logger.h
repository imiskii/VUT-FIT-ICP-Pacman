#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <vector>

using namespace std;

class Logger
{
private:
    Logger();
    ofstream logFile;
    static Logger *logger;

public:
    ~Logger();
    static Logger *access();

    bool createLogFile(vector<string> &fileLines);
    void log(const char *msg);
};

#endif