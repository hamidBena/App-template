#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <mutex>

#ifdef _WIN32
    #define NOMINMAX
    #include <windows.h>
#endif

namespace core {

    enum class LogLevel {
        Trace,
        Info,
        Warn,
        Error,
        Critical
    };

    class Logger {
    public:
        static Logger& get() {
            static Logger instance;
            return instance;
        }

        void setLevel(LogLevel level) { m_level = level; }

        void log(LogLevel level, const std::string& message) {
            if (level < m_level) return;

            std::lock_guard<std::mutex> lock(m_mutex);

            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);

            std::tm tm{};
            #ifdef _WIN32
                localtime_s(&tm, &time);
            #else
                localtime_r(&time, &tm);
            #endif

            std::ostringstream oss;
            oss << "[" << std::put_time(&tm, "%H:%M:%S") << "] ";

            oss << "[" << levelToString(level) << "] " << message << "\n";

            //set and reset the color if on windows
            #ifdef _WIN32
                        setConsoleColor(level);
            #endif
                        std::cout << oss.str();
            #ifdef _WIN32
                        resetConsoleColor();
            #endif
        }

        // Convenience wrappers
        void trace(const std::string& msg) { log(LogLevel::Trace, msg); }
        void info(const std::string& msg) { log(LogLevel::Info, msg); }
        void warn(const std::string& msg) { log(LogLevel::Warn, msg); }
        void error(const std::string& msg) { log(LogLevel::Error, msg); }
        void critical(const std::string& msg) { log(LogLevel::Critical, msg); }

    private:
        Logger() = default;
        ~Logger() = default;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        std::string levelToString(LogLevel level) const {
            switch (level) {
                case LogLevel::Trace: return "TRACE";
                case LogLevel::Info: return "INFO";
                case LogLevel::Warn: return "WARN";
                case LogLevel::Error: return "ERROR";
                case LogLevel::Critical: return "CRITICAL";
            }
            return "UNKNOWN";
        }

#ifdef _WIN32
        void setConsoleColor(LogLevel level) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            WORD color = 7; // default gray
            switch (level) {
                case LogLevel::Trace: color = 8; break; // gray
                case LogLevel::Info: color = 7; break;
                case LogLevel::Warn: color = 14; break; // yellow
                case LogLevel::Error: color = 12; break; // red
                case LogLevel::Critical: color = 4; break; // dark red
            }
            SetConsoleTextAttribute(hConsole, color);
        }

        void resetConsoleColor() {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 7);
        }
#endif

        LogLevel m_level = LogLevel::Trace;
        std::mutex m_mutex;
    };

}
// Macros for convenience
#define CORE_TRACE(msg) ::core::Logger::get().trace(msg)
#define CORE_INFO(msg)  ::core::Logger::get().info(msg)
#define CORE_WARN(msg)  ::core::Logger::get().warn(msg)
#define CORE_ERROR(msg) ::core::Logger::get().error(msg)
#define CORE_CRIT(msg)  ::core::Logger::get().critical(msg)
