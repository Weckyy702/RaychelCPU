/**
*\file Logger.cpp
*\author weckyy702 (weckyy702@gmail.com)
*\brief RaychelLogger implementation file
*\date 2021-06-13
*
*MIT License
*Copyright (c) [2021] [Weckyy702 (weckyy702@gmail.com | https://github.com/Weckyy702)]
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
*
*/

#include "Logger.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <unordered_map>

namespace fs = std::filesystem;

namespace Logger {

    static LogLevel currentLevel = LogLevel::info;
    static LogLevel minLogLevel = LogLevel::info;

    static bool doColor = true;
    constexpr std::string_view reset_col = "\x1b[0m";

    static std::ostream outStream{std::cout.rdbuf()};
    static std::ofstream logFile;

    static std::mutex mtx;
    static bool mtx_engaged;

    static std::unordered_map<std::string_view, timePoint_t> timePoints;

    static std::array<std::string_view, 7> levelLabels = {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL", "FATAL", "OUT"};

    static std::array<std::string_view, 7> cols = {
        "\x1b[36m",     //DEBUG, light blue
        "\x1b[32m",     //INFO, green
        "\x1b[33m",     //WARNING, yellow
        "\x1b[31m",     //ERROR, red
        "\x1b[1;31m",   //CRITICAL, bold red
        "\x1b[4;1;31m", //FATAL bold underlined red
        "\x1b[34m"      //LOG, blue
    };

    std::string_view getLogLabel()
    {
        return levelLabels.at(static_cast<size_t>(currentLevel));
    }

    std::string_view getLogColor()
    {
        return doColor ? cols.at(static_cast<size_t>(currentLevel)) : "";
    }

    namespace _ {

        LogLevel requiredLevel() noexcept
        {
            return minLogLevel;
        }

        void setLogLevel(LogLevel level) noexcept
        {
            currentLevel = level;
        }

        void printWithoutLabel(std::string_view msg) noexcept
        {
            if (doColor) {
                const auto col = getLogColor();
                outStream.write(col.data(), col.size())
                    .write(msg.data(), msg.size())
                    .write(reset_col.data(), reset_col.size());
            } else {
                outStream.write(msg.data(), msg.size());
            }
        }

        void print(std::string_view msg) noexcept
        {
            if (doColor) {
                const auto col = getLogColor();
                const auto label = getLogLabel();

                outStream.write(col.data(), col.size())
                    .write("[", 1)
                    .write(label.data(), label.size())
                    .write("] ", 2)
                    .write(reset_col.data(), reset_col.size());
            } else {
                const auto label = getLogLabel();

                outStream.write("[", 1).write(label.data(), label.size()).write("] ", 2);
            }
            printWithoutLabel(msg);
        }

        void lockStream()
        {
            mtx.lock();
            mtx_engaged = true;
        }

        void unlockStream() noexcept
        {
            if (mtx_engaged) {
                mtx.unlock();
                mtx_engaged = false;
            }
        }

    } // namespace _

    void setLogLabel(LogLevel lv, std::string_view label) noexcept
    {
        _::lockStream();
        [[maybe_unused]] const auto unlock_mutex_on_exit = details::Finally([]() { _::unlockStream(); });

        levelLabels.at(static_cast<size_t>(lv)) = label;
    }

    void setLogColor(LogLevel lv, std::string_view color) noexcept
    {
        _::lockStream();
        [[maybe_unused]] const auto unlock_mutex_on_exit = details::Finally([]() { _::unlockStream(); });

        cols.at(static_cast<size_t>(lv)) = color;
    }

    void setOutStream(std::ostream& os)
    {
        outStream.rdbuf(os.rdbuf());
    }

    void disableColor() noexcept
    {
        doColor = false;
    }

    void enableColor() noexcept
    {
        doColor = true;
    }

    std::string_view startTimer(std::string_view label) noexcept
    {
        const auto tp = std::chrono::high_resolution_clock::now();

        timePoints.insert_or_assign(label, tp);
        return label;
    }

    duration_t endTimer(std::string_view label) noexcept
    {
        using namespace std::chrono;

        const auto endPoint = high_resolution_clock::now();
        if (timePoints.find(label) != timePoints.end()) {
            const auto startTime = timePoints.extract(label).mapped();
            return duration_cast<duration_t>(endPoint - startTime);
        }

        error("Label ", label, " not found!\n");
        return duration_t(-1);
    }

    duration_t getTimer(std::string_view label) noexcept
    {
        using namespace std::chrono;

        const auto endPoint = high_resolution_clock::now();
        if (timePoints.find(label) != timePoints.end()) {
            const auto startTime = timePoints.at(label);
            return duration_cast<duration_t>(endPoint - startTime);
        }
        error("Label ", label, " not found!\n");
        return duration_t(-1);
    }

    void logDuration(std::string_view label, const std::string& _prefix, const std::string& suffix) noexcept
    {
        const auto dur = endTimer(label);
        if (dur.count() != -1) {
            const std::string prefix = (_prefix.empty()) ? (std::string(label) + ": "s) : _prefix;
            info(prefix, dur.count(), suffix);
        }
    }

    void logDurationPersistent(std::string_view label, const std::string& _prefix, const std::string& suffix) noexcept
    {
        const auto dur = getTimer(label);
        if (dur.count() != -1) {
            const std::string prefix = (_prefix.empty()) ? (std::string(label) + ": "s) : _prefix;
            info(prefix, dur.count(), suffix);
        }
    }

    LogLevel setMinimumLogLevel(LogLevel lv) noexcept
    {
        minLogLevel = lv;
        return minLogLevel;
    }

    void initLogFile(const std::string& directory, const std::string& filename)
    {
        const fs::path dir{directory};
        if (!directory.empty()) {
            std::error_code ec;
            fs::create_directories(dir, ec);

            if (ec) {
                error("failed to open log file '", directory, "/", filename, "': ", ec.message());
            }
        }

        if (logFile.is_open()) {
            dumpLogFile();
        }

        const fs::path filepath = dir / filename;

        logFile = std::ofstream{filepath};
        outStream.rdbuf(logFile.rdbuf());
    }

    void dumpLogFile() noexcept
    {
        if (logFile.is_open()) {
            if (outStream.rdbuf() == logFile.rdbuf()) {
                outStream.rdbuf(std::cout.rdbuf());
            }
            logFile.close();
        }
    }
} // namespace Logger
