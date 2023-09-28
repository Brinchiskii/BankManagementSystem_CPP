//
// Created by Sebastian Brinch on 26/08/2023.
//

#include <iostream>
#include <string>

#include "logger.h"

Logger::Logger(const std::string &filename) {
    logFile.open(filename, std::ios_base::app);
}

Logger::~Logger() {
    if(logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(LogLevel level, const std::string &message) {
    std::string levelStr = getLogLevelString(level);
    std::string timestamp = getCurrentTimestamp();

    std::string logMessage = "[" + timestamp + "] [" + levelStr + "] " + message;

    if(logFile.is_open()) {
        logFile << logMessage << std::endl;
    }
}

std::string Logger::getLogLevelString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";

    }
}

std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    char timestampBuffer[80];
    std::strftime(timestampBuffer, sizeof(timestampBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));
    return timestampBuffer;
}