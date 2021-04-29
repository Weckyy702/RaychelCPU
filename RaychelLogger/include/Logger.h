/*
 * Logger.h
 *
 *  Created on: 18.02.2021
 *      Author: weckyy
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#if !((defined(__cplusplus) && (__cplusplus >= 201703L)) || defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
#error "C++17 compilation is required!"
#endif

#include "Helper.h"

#include <string>
#include <string_view>
#include <chrono>
#include <type_traits>
#include <sstream>
#include <array>

namespace Logger {
	enum class LogLevel : size_t { debug=0u, info, warn, error, critical, fatal, log };

	using namespace std::string_literals;

	typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint_t;
	typedef std::chrono::milliseconds duration_t;

	namespace _ {

		//internal function. Not to be used directly
		LogLevel requiredLevel();

		//internal function. Not to be used directly
		void setLogLevel(LogLevel);

		//internal function. Not to be used directly
		void printWithoutLabel(std::string_view);

		//internal function. Not to be used directly
		void print(std::string_view);

		void lockStream();

		void unlockStream();

		//internal function. Not to be used directly
		template<typename T>
		std::string getRepNonStreamable(T&& obj) {
			std::ostringstream interpreter;

			interpreter << details::type_name<std::remove_reference_t<T>>() << " at 0x" << std::hex << (uintptr_t)&obj;

			return interpreter.str();
		}

		template<typename T>
		std::string getRepStreamable(T&& obj) {
			std::ostringstream interpreter;

			interpreter << obj;

			return interpreter.str();
		}

		template<typename T, typename = std::enable_if_t<!std::is_same_v<T, const char*>>>
		std::string getRepStreamable(T* obj) {
			std::ostringstream interpreter;

			interpreter << details::type_name<T>() << "* at 0x" << std::hex << (uintptr_t)obj;

			return interpreter.str();
		}

		//overload getRepStreamable so C-style strings don't get logged as pointers
		template<typename = void>
		std::string getRepStreamable(const char* obj)
		{
			return std::string(obj);
		}

		//internal function. Not to be used directly
		template<typename T, std::enable_if_t<details::is_to_stream_writable_v<std::ostringstream, T>, bool> = true>
		void logObj(bool log_with_label, T&& obj) {
				std::string representation = getRepStreamable(std::forward<T>(obj));

			if (log_with_label)
				print(representation);
			else
				printWithoutLabel(representation);
		}

		//internal function. Not to be used directly
		template<typename T, std::enable_if_t<!details::is_to_stream_writable_v<std::ostringstream, T>, bool> = false>
		void logObj(bool log_with_label, T&& obj) {
			std::string representation = getRepNonStreamable(std::forward<T>(obj));

			if (log_with_label)
				print(representation);
			else
				printWithoutLabel(representation);
		}

		template<typename T, typename... Args>
		void logConcurrent(LogLevel lv, bool log_with_label, T&& obj, Args&&... args)
		{
			lockStream();
			auto _ = details::Finally([](){ unlockStream(); });

			if(lv < _::requiredLevel()) return;
			setLogLevel(lv);

			logObj(log_with_label, std::forward<T>(obj));
			(logObj(false, std::forward<Args>(args)), ...);
		}

		template<typename... Args>
		void log(LogLevel lv, bool log_with_label, Args&&... args) {
			_::logConcurrent(lv, log_with_label, std::forward<Args>(args)...);
		}
	}

	/// \brief Log a message with the provided level. Can log multiple objects seperated by a comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param lv the level with which to log
	/// \param ...args Objects to be logged
	template<typename... Args>
	void log(LogLevel lv, Args&&... args)
	{
		_::log(lv, true, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the DEBUG level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void debug(Args&&... args)
	{
		_::log(LogLevel::debug, true, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the INFO level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void info(Args&&... args)
	{
		_::log(LogLevel::info, true, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the WARN level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void warn(Args&&... args)
	{
		_::log(LogLevel::warn, true, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the ERROR level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void error(Args&&... args)
	{
		_::log(LogLevel::error, true, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the ERROR level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void critical(Args&&... args)
	{
		_::log(LogLevel::critical, true, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the FATAL level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void fatal(Args&&... args)
	{
		_::log(LogLevel::fatal, true, std::forward<Args>(args)...);
	}

	/// \brief Log a message regardless of the minimum required log level. Can log multiple objects seperated by a comma.
	///        will not display a label [LEVEL] in front of the message
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void log(Args&&... args) {
		_::log(LogLevel::log, false, std::forward<Args>(args)...);
	}

	//set the label that is displayed in front of the message [LABEL] msg
	void setLogLabel(LogLevel, std::string_view);

	//set the color that should be used for the level. Must be an ANSI compatible color code
	void setLogColor(LogLevel, std::string_view);

	//set an alternative stream for the logger to write to
	void setOutStream(std::ostream& os);

	//disable colored output
	void disableColor();

	//enable colored output
	void enableColor();

	//start a timer and associate it with the label
	std::string_view startTimer(std::string_view label);

	//return the duration since the last call to startTimer(label). removes label from the list of active labels
	duration_t endTimer(std::string_view label);

	//return the duration since the last call to startTimer(label). does NOT remove label from the list of acitve labels
	duration_t getTimer(std::string_view label);

	//log the duration since the last call to startTimer(label). removes label from the list of active labels
	void logDuration(std::string_view label, const std::string& prefix = ""s, const std::string& suffix = "ms\n"s);

	//log the duration since the last call to startTimer(label). does NOT remove label from the list of acitve labels
	void logDurationPersistent(std::string_view label, const std::string& prefix=""s, const std::string& suffix = "ms\n"s);

	//set minimum level the Message has to be sent with in order to show up. Default: INFO
	LogLevel setMinimumLogLevel(LogLevel);

	/// \brief Configure the Logger to log into a file instead of a std::ostream
	/// \param directory Directory of the logfile. must end with "/"
	/// \param fileName Name of the logfile. Does not need an extension
	void initLogFile(const std::string& directory, const std::string& fileName = "Log.log");

	void dumpLogFile();
}


#endif /* LOGGER_H_ */
