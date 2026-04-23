// Logger.hpp
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <mutex>
#include <string>

enum class LogLevel {
    Debug = 0,
    Info,
    Warn,
    Error
};

class Logger {
public:
    static void SetMinLevel(LogLevel level);
    static void Log(LogLevel level, const std::string& msg);

private:
    static const char* LevelToString(LogLevel level);

private:
    static LogLevel minLevel;
    static std::mutex logMutex;
};

#define LOG_DEBUG(msg) Logger::Log(LogLevel::Debug, (msg))
#define LOG_INFO(msg)  Logger::Log(LogLevel::Info,  (msg))
#define LOG_WARN(msg)  Logger::Log(LogLevel::Warn,  (msg))
#define LOG_ERROR(msg) Logger::Log(LogLevel::Error, (msg))

#endif // LOGGER_HPP