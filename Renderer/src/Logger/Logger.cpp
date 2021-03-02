#include "Logger.h"

#include <iostream>

Logger Logger::m_Instace;
HANDLE Logger::m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void Logger::Info(const std::string& log)
{
	InfoColor();
	std::cout << "[INFO]: " << log << std::endl;
}

void Logger::Warn(const std::string& log)
{
	WarnColor();
	std::cout << "[WARNING]: " << log << std::endl;
}

void Logger::Critical(const std::string& log)
{
	CriticalColor();
	std::cout << "[CRITICAL]: " << log << std::endl;
}

void Logger::InfoColor()
{
	SetConsoleTextAttribute(m_stdHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void Logger::WarnColor()
{
	SetConsoleTextAttribute(m_stdHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void Logger::CriticalColor()
{
	SetConsoleTextAttribute(m_stdHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
}