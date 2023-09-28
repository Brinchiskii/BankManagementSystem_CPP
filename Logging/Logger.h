//
// Created by Sebastian Brinch on 26/08/2023.
//

#ifndef BANKMANAGEMENTSYSTEM_LOGGER_H
#define BANKMANAGEMENTSYSTEM_LOGGER_H

#include <fstream>
#include <string>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger{
public:
    Logger(const std::string& filename);
    ~Logger();

    void log(LogLevel level, const std::string& message);

private:
    std::ofstream logFile;

    std::string getLogLevelString(LogLevel level);
    std::string getCurrentTimestamp();
};

#endif //BANKMANAGEMENTSYSTEM_LOGGER_H
