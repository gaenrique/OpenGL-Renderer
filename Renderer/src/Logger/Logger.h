#pragma once

#include <string>
#include <Windows.h>

#include <iostream>

/*
This Logger class is meant to act as a Singleton

There are three types of Logs that can be outputted to stdout.
	1. INFO
	2. WARN
	3. CRITICAL

The type of log is simply chosen by either logging with Logger::Info(...),
Logger::Warn(...) or Logger::Critical(...). These three types of Log Levels 
are outputted to stdout in different colors and formats.

These Log Levels are used in a way that the current LogLevel can be set,
causing only that log level and any above it to be seen on stdout

Another important feature of this logging system is formatting.
An example is shown below:

Logger::Info("Vertex positions: {} {} {}", 1.0f, 0.2f, -0.1f)

The string can contain the format specifier {}, these are filled in in order
with the argument that follow. These arguments can vary in type.
*/

enum LogLevel
{
	INFO,
	WARN,
	CRITICAL
};

class Logger
{
public:
	// Making the class static
	Logger(const Logger&) = delete;
	Logger operator=(const Logger&) = delete;

	template<typename... Args>
	static void Info(const std::string& log, Args... args)
	{
		InfoColor();
		std::cout << "[INFO]: ";
		int currentIndex = 0;
		Log(log, currentIndex, args...);
	}

	template<typename... Args>
	static void Warn(const std::string& log, const Args&... args)
	{
		WarnColor();
		std::cout << "[WARNING]: ";
		int currentIndex = 0;
		Log(log, currentIndex, args...);
	}

	template<typename... Args>
	static void Critical(const std::string& log, const Args&... args)
	{
		CriticalColor();
		std::cout << "[CRITICAL]: ";
		int currentIndex = 0;
		Log(log, currentIndex, args...);
	}

private:
	Logger() {};

	/*
	This two log methods are used to unpack the variadic template.

	In order for this to work, there needs to be two versions of the method. One containing a single template element
	and another one containing a template element and a variadic template element. This allows for recursion until reaching
	the final 'only one template element left' method

	Note that the current index is passed by reference as its increasing value is passed recursively

	TODO: make a static variable for the stdout HANDLE
	*/
	template<typename Head, typename... Tail>
	static void Log(const std::string& log, int& currentIndex, const Head& head, const Tail&... tail)
	{
		for (int i = currentIndex; i < log.size(); i++)
		{
			// Reached a format specifier
			if (log[i] == '{' && log[i + 1] == '}')
			{
				std::cout << head;
				currentIndex += 2;
				break;
			}
			std::cout << log[i];
			currentIndex++;
		}
		Log(log, currentIndex, tail...);
	}

	template<typename Head>
	static void Log(const std::string& log, int& currentIndex, const Head& head)
	{
		for (int i = currentIndex; i < log.size(); i++)
		{
			if (log[i] == '{' && log[i + 1] == '}')
			{
				std::cout << head;
				currentIndex += 2;
				break;
			}
			std::cout << log[i];
			currentIndex++;
		}
		std::cout << std::endl;
	}

	static void Log(const std::string& log, int& currentIndex)
	{
		std::cout << log << std::endl;
	}

	static void InfoColor()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}

	static void  WarnColor()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	static void CriticalColor()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	}
};