// Logger.cpp
#include "Logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

LogLevel Logger::minLevel = LogLevel::Debug;
std::mutex Logger::logMutex;

void Logger::SetMinLevel(LogLevel level) {
    minLevel = level;
}

const char* Logger::LevelToString(LogLevel level) {
    switch (level) {
    case LogLevel::Debug: return "DEBUG";
    case LogLevel::Info:  return "INFO";
    case LogLevel::Warn:  return "WARN";
    case LogLevel::Error: return "ERROR";
    default:              return "UNKNOWN";
    }
}

void Logger::Log(LogLevel level, const std::string& msg) {
    if (static_cast<int>(level) < static_cast<int>(minLevel)) {
        return;
    }

    std::lock_guard<std::mutex> lock(logMutex);

    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::tm tmBuf{};
#ifdef _WIN32
    localtime_s(&tmBuf, &t);
#else
    localtime_r(&t, &tmBuf);
#endif

    std::cout << '[' << std::put_time(&tmBuf, "%H:%M:%S") << "] "
              << '[' << LevelToString(level) << "] "
              << msg << '\n' << std::flush;
}