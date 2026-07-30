#include "logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

Logger& Logger::getInstance()
{
    static Logger logger;

    return logger;
}

Logger::Logger()
{
    logFile.open("logs/server.log", std::ios::app);
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

std::string Logger::getCurrentTime()
{
    auto now =
        std::chrono::system_clock::now();

    std::time_t currentTime =
        std::chrono::system_clock::to_time_t(now);

    std::tm* localTime =
        std::localtime(&currentTime);

    std::ostringstream output;

    output << std::put_time(
        localTime,
        "%Y-%m-%d %H:%M:%S");

    return output.str();
}

void Logger::info(const std::string& message)
{
    std::lock_guard<std::mutex> lock(logMutex);

    std::string log =
        getCurrentTime() +
        " [INFO] " +
        message;

    std::cout << log << std::endl;

    if (logFile.is_open())
    {
        logFile << log << std::endl;
    }
}

void Logger::error(const std::string& message)
{
    std::lock_guard<std::mutex> lock(logMutex);

    std::string log =
        getCurrentTime() +
        " [ERROR] " +
        message;

    std::cerr << log << std::endl;

    if (logFile.is_open())
    {
        logFile << log << std::endl;
    }
}