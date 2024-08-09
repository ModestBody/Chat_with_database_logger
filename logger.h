#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <mutex>
#include <shared_mutex>

class Logger {
public:
    Logger(const std::string& filename);

    ~Logger();

    void log(const std::string& message);

    std::string readLog();

private:
    std::fstream log_file;
    std::shared_mutex mutex_;
};

#endif // LOGGER_H


