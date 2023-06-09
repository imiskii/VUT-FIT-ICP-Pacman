/**
 * @file Logger.cpp
 * @author Adam Lazík (xlazik00)
 * @brief Implementation of logger class for logging games.
 */

#include "Logger.h"

Logger::Logger()
{
    _enabled = false;
}

Logger::~Logger()
{
    if(logFile.is_open())
    {
        logFile.close();
    }
}

bool Logger::createLogFile(vector<string> &fileLines)
{
    if(!_enabled)
    {
        return true;
    }

    if(!filesystem::is_directory("../../logs"))
    {
        if(!filesystem::create_directory("../../logs"))
        {
            cerr << "Warning: failed to create logs directory. Logs will not be stored." << endl;
        }
    }
    if (logFile.is_open())
    {
        logFile.close();
    }

    // Get current time as timestamp
    auto currentTime = chrono::system_clock::now();
    time_t timestamp = chrono::system_clock::to_time_t(currentTime);

    // Format timestamp as string
    stringstream filename;
    filename << "../../logs/game_" << std::put_time(std::localtime(&timestamp), "%Y-%m-%d_%H:%M:%S") << ".txt";

    logFile = ofstream(filename.str());
    if (!logFile.is_open())
    {
        cerr << "Warning: failed to open log file. The game will not be logged." << endl;
        return false;
    }
    else
    {
        for (auto line: fileLines)
        {
            logFile << line << endl;
        }
        return true;
    }
}

void Logger::log(string msg)
{
    if (_enabled)
    {
        logFile << msg << endl;
    }
}

void Logger::enable()
{
    _enabled = true;
}

void Logger::disable()
{
    _enabled = false;
}
