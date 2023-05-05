#include "Logger.h"
#include <iostream>

Logger *Logger::logger = nullptr;

Logger::Logger() {}

Logger::~Logger()
{
    if (logger != nullptr)
    {
        if(logger->logFile.is_open())
        {
            logger->logFile.close();
        }
        delete logger;
    }
}

Logger *Logger::access()
{
    if (logger == nullptr)
    {
        logger = new Logger();
    }
    return logger;
}

bool Logger::createLogFile(vector<string> &fileLines)
{
    if (logFile.is_open())
    {
        logFile.close();
    }
    logFile = ofstream("../../logs/log1");
    for (auto line: fileLines)
    {
        logFile << line << endl;
    }
    return true;
}

void Logger::log(const char *msg)
{
    logFile << msg << endl;
}