#pragma once

#include <fstream>
#include <mutex>
#include <string>

class Logger
{
public:
    static Logger& getInstance();

    void info(const std::string& message);

    void error(const std::string& message);

private:
    Logger();
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::ofstream logFile;

    std::mutex logMutex;

    std::string getCurrentTime();
};