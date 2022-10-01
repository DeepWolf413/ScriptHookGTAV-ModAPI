#include "Logger.h"

namespace ModAPI::Logging
{
	bool Logger::isLoggingEnabled = true;
	std::unique_ptr<Logger> Logger::currentLogger;

	Logger::Logger(const std::string& loggerName)
	{ name = loggerName; }

	Logger::Logger(Logger&& loggerToMove) noexcept : name(std::move(loggerToMove.name))
	{}

	Logger& Logger::operator=(Logger&& loggerToMove) noexcept
	{
		name = std::move(loggerToMove.name);
		return *this;
	}

	void Logger::SetLogger(std::unique_ptr<Logger> loggerToUse)
	{ currentLogger = std::move(loggerToUse); }

	void Logger::EnableLogging(const bool enable)
	{ isLoggingEnabled = enable; }

	bool Logger::TryLogInfo(const std::string& message)
	{
		const auto logger = Get();
		if (logger ==  nullptr)
		{ return false; }

		logger->LogInfo(message);
		return true;
	}

	bool Logger::TryLogWarning(const std::string& message)
	{
		const auto logger = Get();
		if (logger ==  nullptr)
		{ return false; }

		logger->LogWarning(message);
		return true;
	}

	bool Logger::TryLogError(const std::string& message)
	{
		const auto logger = Get();
		if (logger ==  nullptr)
		{ return false; }

		logger->LogError(message);
		return true;
	}

	Logger* Logger::Get()
	{ return currentLogger.get(); }
}
