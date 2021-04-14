/*
 * Logger.h
 *
 *  Created on: 18.02.2021
 *      Author: weckyy
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#if !defined(__cplusplus) || (__cplusplus < 201703L)
#error "C++17 compilation is required!"
#endif

#ifdef _WIN32
	#ifdef LOGGER_EXPORTS
		#define LOGGER_API __declspec(dllexport)
	#else
		#define LOGGER_API __declspec(dllimport)
	#endif
#else
	#define LOGGER_API
#endif

#include "Helper.h"

#include <string>
#include <string_view>
#include <chrono>
#include <type_traits>
#include <sstream>
#include <array>
#include <gsl/gsl>

namespace Logger {
	enum class LogLevel : size_t { debug=0u, info, warn, error, critical, fatal, log };

	using namespace std::string_literals;

	typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint_t;
	typedef std::chrono::milliseconds duration_t;

	namespace _ {

		//internal function. Not to be used directly
		LOGGER_API LogLevel requiredLevel();

		//internal function. Not to be used directly
		LOGGER_API void setLogLevel(LogLevel);

		//internal function. Not to be used directly
		LOGGER_API void printWithoutLabel(std::string_view);

		//internal function. Not to be used directly
		LOGGER_API void print(std::string_view);

		LOGGER_API void lockStream();

		LOGGER_API void unlockStream();

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

		template<typename T, class = std::enable_if_t<!std::is_same_v<T, const char*>>>
		std::string getRepStreamable(T* obj) {
			std::ostringstream interpreter;

			interpreter << details::type_name<T>() << "* at 0x" << std::hex << (uintptr_t)obj;

			return interpreter.str();
		}

		//overload getRepStreamable so C-style strings don't get logged as pointers
		template<class = void>
		std::string getRepStreamable(const char* obj)
		{
			return std::string(obj);
		}

		//internal function. Not to be used directly
		template<typename T>
		void logObj(size_t depth, T&& obj) {
			std::string representation;

			//check if obj can be represented as a string
			if constexpr (details::is_to_stream_writable_v<std::ostringstream, T>)
				representation = getRepStreamable(std::forward<T>(obj));
			else
				representation = getRepNonStreamable(std::forward<T>(obj));

			if (depth == 0)
				print(representation);
			else
				printWithoutLabel(representation);
		}

		//internal function. Not to be used directly
		template<typename T, typename... Args>
		void logObj(size_t depth, T&& obj, Args&&... args) {
			logObj(depth, std::forward<T>(obj));
			logObj(depth + 1, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void logConcurrent(LogLevel lv, size_t depth, Args&&... args)
		{
			lockStream();
			auto _ = gsl::finally([](){ unlockStream(); });
			if(lv < _::requiredLevel()) return;
			setLogLevel(lv);
			logObj(depth, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void log(LogLevel lv, size_t depth, Args&&... args) {
			_::logConcurrent(lv, depth, std::forward<Args>(args)...);
		}
	}

	/// \brief Log a message with the provided level. Can log multiple objects seperated by a comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param lv the level with which to log
	/// \param ...args Objects to be logged
	template<typename... Args>
	void log(LogLevel lv, Args&&... args)
	{
		_::log(lv, 0, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the DEBUG level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void debug(Args&&... args)
	{
		_::log(LogLevel::debug, 0, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the INFO level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void info(Args&&... args)
	{
		_::log(LogLevel::info, 0, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the WARN level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void warn(Args&&... args)
	{
		_::log(LogLevel::warn, 0, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the ERROR level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void error(Args&&... args)
	{
		_::log(LogLevel::error, 0, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the ERROR level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void critical(Args&&... args)
	{
		_::log(LogLevel::critical, 0, std::forward<Args>(args)...);
	}

	/// \brief Log a message with the FATAL level. Can log multiple objects seperated by comma
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void fatal(Args&&... args)
	{
		_::log(LogLevel::fatal, 0, std::forward<Args>(args)...);
	}

	/// \brief Log a message regardless of the minimum required log level. Can log multiple objects seperated by a comma.
	///        will not display a label [LEVEL] in front of the message
	/// \tparam ...Args Types of the objects to be logged
	/// \param ...args Objects to be logged
	template<typename... Args>
	void log(Args&&... args) {
		_::log(LogLevel::log, 1, std::forward<Args>(args)...);
	}

	//set the label that is displayed in front of the message [LABEL] msg
	LOGGER_API void setLogLabel(LogLevel, std::string_view);

	//set the color that should be used for the level. Must be an ANSI compatible color code
	LOGGER_API void setLogColor(LogLevel, std::string_view);

	//set an alternative stream for the logger to write to
	LOGGER_API void setOutStream(std::ostream& os);

	//disable colored output
	LOGGER_API void disableColor();

	//enable colored output
	LOGGER_API void enableColor();

	//start a timer and associate it with the label
	LOGGER_API std::string_view startTimer(std::string_view label);

	//return the duration since the last call to startTimer(label). removes label from the list of active labels
	LOGGER_API duration_t endTimer(std::string_view label);

	//return the duration since the last call to startTimer(label). does NOT remove label from the list of acitve labels
	LOGGER_API duration_t getTimer(std::string_view label);

	//log the duration since the last call to startTimer(label). removes label from the list of active labels
	LOGGER_API void logDuration(std::string_view label, const std::string& prefix = ""s, const std::string& suffix = "ms\n"s);

	//log the duration since the last call to startTimer(label). does NOT remove label from the list of acitve labels
	LOGGER_API void logDurationPersistent(std::string_view label, const std::string& prefix=""s, const std::string& suffix = "ms\n"s);

	//set minimum level the Message has to be sent with in order to show up. Default: INFO
	LOGGER_API LogLevel setMinimumLogLevel(LogLevel);

	/// \brief Configure the Logger to log into a file instead of a std::ostream
	/// \param directory Directory of the logfile. must end with "/"
	/// \param fileName Name of the logfile. Does not need an extension
	LOGGER_API void initLogFile(const std::string& directory, const std::string& fileName = "Log.log");

	LOGGER_API void dumpLogFile();
}


#endif /* LOGGER_H_ */
