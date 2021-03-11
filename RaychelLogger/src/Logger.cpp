#include "Logger.h"

#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <mutex>

namespace fs = std::filesystem;

namespace Logger {

	static LogLevel currentLevel = LogLevel::info;
	static LogLevel minLogLevel = LogLevel::info;

	static bool doColor = true;
	constexpr std::string_view reset_col = "\x1b[0;0m";

	static std::ostream outStream { std::cout.rdbuf() };
	static std::ofstream logFile;

	static std::mutex mtx;

	static std::unordered_map<std::string_view, timePoint_t> timePoints;

	static std::array<std::string_view, 7> levelLabels = {
			"DEBUG",
			"INFO",
			"WARNING",
			"ERROR",
			"CRITICAL",
			"FATAL",
			"OUT"
	};

	static std::array<std::string_view, 7> cols = {
			"\x1b[36m", 	//DEBUG, light blue
			"\x1b[32m",		//INFO, green
			"\x1b[33m",		//WARNING, yellow
			"\x1b[31m",		//ERROR, red
			"\x1b[31;43m",	//CRITICAL, red;orange background
			"\x1b[0;41m",	//FATAL white;red background
			"\x1b[34m"		//LOG, blue
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

		LogLevel requiredLevel()
		{
			return minLogLevel;
		}

		void setLogLevel(LogLevel level)
		{
			currentLevel = level;
		}

		void printWithoutLabel(std::string_view msg)
		{
			if (currentLevel >= minLogLevel) {
				if(doColor) {
					auto col = getLogColor();
					outStream
					.write(col.data(), col.size())
					.write(msg.data(), msg.size())
					.write(reset_col.data(), reset_col.size());
				} else {
					outStream.write(msg.data(), msg.size());
				}
			}
		}

		void print(std::string_view msg)
		{
			if (currentLevel >= minLogLevel) {
				if(doColor) {
					auto col = getLogColor();
					auto label = getLogLabel();

					outStream
					.write(col.data(), col.size())
					.write("[", 1)
					.write(label.data(), label.size())
					.write("] ", 2)
					.write(reset_col.data(), reset_col.size());
				} else {
					auto label = getLogLabel();

					outStream
					.write("[", 1)
					.write(label.data(), label.size())
					.write("] ", 2);
				}
				printWithoutLabel(msg);
			}
		}

		void lockStream()
		{
			mtx.lock();
		}

		void unlockStream()
		{
			mtx.unlock();
		}

	}

	void setLogLabel(LogLevel lv, std::string_view label)
	{
		_::lockStream();
		auto _ = gsl::finally([](){ _::unlockStream(); });
		levelLabels.at(static_cast<size_t>(lv)) = label;
	}

	void setLogColor(LogLevel lv, std::string_view color)
	{
		_::lockStream();
		auto _ = gsl::finally([](){ _::unlockStream(); });
		cols.at(static_cast<size_t>(lv)) = color;
	}

	void setOutStream(std::ostream& os)
	{
		outStream.rdbuf(os.rdbuf());
	}

	void disableColor()
	{
		doColor = false;
	}

	void enableColor()
	{
		doColor = true;
	}

	std::string_view startTimer(std::string_view label)
	{
		timePoint_t tp = std::chrono::high_resolution_clock::now();
		timePoints.insert_or_assign(label, tp);
		return label;
	}

	duration_t endTimer(std::string_view label)
	{
		using namespace std::chrono;
		auto endPoint = high_resolution_clock::now();
		if (timePoints.find(label) != timePoints.end()) {
			auto startTime = timePoints.extract(label).mapped();
			return duration_cast<duration_t>(endPoint - startTime);
		} else {
			error("Label ", label, " not found!\n");
			return duration_t(-1);
		}
	}

	duration_t getTimer(std::string_view label)
	{
		using namespace std::chrono;
		auto endPoint = high_resolution_clock::now();
		if (timePoints.find(label) != timePoints.end()) {
			auto startTime = timePoints.at(label);
			return duration_cast<duration_t>(endPoint - startTime);
		} else {
			error("Label ", label, "not found!\n");
			return duration_t(-1);
		}
	}

	void logDuration(std::string_view label, const std::string& _prefix,
			const std::string& suffix)
	{
		duration_t dur = endTimer(label);
		if (dur.count() != -1) {
			std::string prefix =
					(_prefix == "") ? std::string(label) + ": "s : _prefix;
			info(prefix, dur.count(), suffix);
		}
	}

	void logDurationPersistent(std::string_view label, const std::string& _prefix,
			const std::string& suffix)
	{
		duration_t dur = getTimer(label);
		if (dur.count() != -1) {
			std::string prefix =
					(_prefix == "") ? std::string(label) + ": "s : _prefix;
			info(prefix, dur.count(), suffix);
		}
	}

	LogLevel setMinimumLogLevel(LogLevel lv)
	{
		minLogLevel = lv;
		return minLogLevel;
	}

	void initLogFile(const std::string& directory, const std::string& filename)
	{
		fs::path dir{directory};
		fs::path filepath = dir / filename;
		if(directory != "") {
			std::error_code ec;
			fs::create_directories(dir, ec);
		}
		if(logFile.is_open()) {
			dumpLogFile();
		}
		logFile = std::ofstream{filepath};
		outStream.rdbuf(logFile.rdbuf());
	}

	void dumpLogFile()
	{
		if(outStream.rdbuf() == logFile.rdbuf()) {
			outStream.rdbuf(std::cout.rdbuf());
		}
		logFile.close();
	}
}
