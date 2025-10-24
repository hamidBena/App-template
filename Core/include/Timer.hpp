#pragma once
#include <chrono>
#include <string>
#include <iostream>

namespace core {

class Timer {
public:
    explicit Timer(std::string name = "", bool printOnDestruct = false)
        : m_startTime(std::chrono::high_resolution_clock::now()),
          m_scopeName(std::move(name)),
          m_printOnDestruct(printOnDestruct) {}

    ~Timer() {
        if (m_printOnDestruct)
            Print();
    }

    // Move-only semantics (safe for scoped timers)
    Timer(Timer&& other) noexcept
        : m_startTime(other.m_startTime),
          m_endTime(other.m_endTime),
          m_scopeName(std::move(other.m_scopeName)),
          m_stopped(other.m_stopped),
          m_printOnDestruct(other.m_printOnDestruct)
    {
        other.m_stopped = true; // avoid double stop
        other.m_printOnDestruct = false;
    }

    Timer& operator=(Timer&& other) noexcept {
        if (this != &other) {
            m_startTime = other.m_startTime;
            m_endTime = other.m_endTime;
            m_scopeName = std::move(other.m_scopeName);
            m_stopped = other.m_stopped;
            m_printOnDestruct = other.m_printOnDestruct;

            other.m_stopped = true;
            other.m_printOnDestruct = false;
        }
        return *this;
    }

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    // Timing controls
    void Stop() {
        if (!m_stopped) {
            m_endTime = std::chrono::high_resolution_clock::now();
            m_stopped = true;
        }
    }

    double Reset() {
        auto elapsed = GetElapsed();
        m_startTime = std::chrono::high_resolution_clock::now();
        m_stopped = false;

        return elapsed;
    }

    bool IsStopped() const { return m_stopped; }

    // elapsed time (ms)
    [[nodiscard]] double GetElapsed() const {
        using namespace std::chrono;
        auto endTime = m_stopped ? m_endTime : high_resolution_clock::now();    // if the timer is stopped use endTime, else use the current "now"
        auto duration = duration_cast<microseconds>(endTime - m_startTime).count();
        return static_cast<double>(duration) / 1000.0;
    }

    operator double() const { return GetElapsed(); }

    const std::string& GetName() const { return m_scopeName; }

    void Print() const {
        std::cout << "[TIMER] " << (m_scopeName.empty() ? "(unnamed)" : m_scopeName)
                  << ": " << GetElapsed() << " ms" << std::endl;
    }

private:
    std::chrono::high_resolution_clock::time_point m_startTime;
    std::chrono::high_resolution_clock::time_point m_endTime;
    std::string m_scopeName;
    bool m_stopped = false;
    bool m_printOnDestruct = true;
};

}
