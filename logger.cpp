#include "logger.h"
#include <stdexcept>

Logger::Logger(const std::string& filename) : log_file(filename, std::ios::app) {
    if (!log_file.is_open()) {
        throw std::runtime_error("Unable to open log file");
    }
}

Logger::~Logger() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (log_file.is_open()) {
        log_file.close();
    }
}

void Logger::log(const std::string& message) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    log_file << message << std::endl;
}

std::string Logger::readLog() {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    std::string line;
    if (std::getline(log_file, line)) {
        return line;
    }
    return "";
}
