#pragma once

#include <string>
#include <Windows.h>

enum LogLevel
{
	INFO,
	WARN,
	CRITICAL
};

class Logger
{
public:
	Logger(const Logger&) = delete;

	Logger operator=(const Logger&) = delete;

	static void Info(const std::string& log);

	static void Warn(const std::string& log);

	static void Critical(const std::string& log);

private:
	Logger() {};

	void Log(const std::string&);

	static void InfoColor();
	static void  WarnColor();
	static void CriticalColor();

	static Logger m_Instace;
	// This is the handle for stdout (MSDN documentation)
	static HANDLE m_stdHandle;
};