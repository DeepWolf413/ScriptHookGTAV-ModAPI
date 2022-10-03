#include "LoggerConsole.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "Camera.h"

namespace ModAPI::Logging
{
	LoggerConsole::LoggerConsole(const std::string& loggerName) : Logger(loggerName)
	{
		AllocateConsole();
	}

	LoggerConsole::LoggerConsole(LoggerConsole&& loggerToMove) noexcept : Logger(std::move(loggerToMove)), currentTextColorId(loggerToMove.currentTextColorId)
	{}

	LoggerConsole::~LoggerConsole()
	{
		fclose(stdout);
		fclose(stderr);
		FreeConsole();
	}

	LoggerConsole& LoggerConsole::operator=(LoggerConsole&& loggerToMove) noexcept
	{
		name = std::move(loggerToMove.name);
		currentTextColorId = loggerToMove.currentTextColorId;
		return *this;
	}

	void LoggerConsole::LogInfo(const std::string& message)
	{
		currentTextColorId = 15;
		LoggerConsole::Log(message);
	}

	void LoggerConsole::LogWarning(const std::string& message)
	{
		currentTextColorId = 14;
		LoggerConsole::Log(message);
	}
	
	void LoggerConsole::LogError(const std::string& message)
	{
		currentTextColorId = 12;
		LoggerConsole::Log(message);
	}

	void LoggerConsole::Log(const std::string& message)
	{
		if (!isLoggingEnabled)
		{ return; }
		
		const auto time = std::time(nullptr);
		const auto localTime = *std::localtime(&time);
		
		std::ostringstream stringStream;
		stringStream << std::put_time(&localTime, "%X");
	
		const auto timeString = stringStream.str();

		HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(outputHandle, currentTextColorId);
		std::cout << "[" << timeString << "]: " << message << std::endl;
	}

	void LoggerConsole::AllocateConsole() const
	{
		AllocConsole();
		SetConsoleTitleA(name.c_str());

		FILE* pCout;
		freopen_s(&pCout, "CONOUT$", "w", stdout);
		freopen_s(&pCout, "CONOUT$", "w", stderr);
		std::cout.clear();
		std::clog.clear();
		std::cerr.clear();
	}
}
