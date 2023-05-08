/**
 * @file Logger.cpp
 * @author Adam Lazík (xlazik00)
 * @brief Declaration of logger class for logging games.
 */

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

/**
 * @brief class implementing game logging service
 */
class Logger
{
private:
    ofstream logFile; ///< file to which the game is being logged
    bool _enabled;    ///< flag indicating whether logger is enabled

public:
    Logger();
    ~Logger();

    /**
     * @brief enable game logging
     */
    void enable();

    /**
     * @brief disable game logging
     */
    void disable();

    /**
     * @brief create a new file in logs/ directory with the current timestamp
     * @param fileLines textual representation of currently loaded map
     * extracted from map file
     * @return true if the file was opened successfully
     * @return false if the file was not opened successfully
     */
    bool createLogFile(vector<string> &fileLines);

    /**
     * @brief print a line to log file and end it with new line
     * @param msg line to be printed
     */
    void log(string msg);
};

#endif
