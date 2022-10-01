#pragma once
#include <memory>
#include <string>

namespace ModAPI::Logging
{
	class Logger
	{
	public:
		Logger(const std::string& loggerName);
		Logger(const Logger& loggerToCopy) = default;
		Logger(Logger&& loggerToMove) noexcept;
		virtual ~Logger() = default;

		Logger& operator=(const Logger& loggerToCopy) noexcept = default;
		Logger& operator=(Logger&& loggerToMove) noexcept;

		static void SetLogger(std::unique_ptr<Logger> loggerToUse);
		static void EnableLogging(bool enable);
		static bool TryLogInfo(const std::string& message);
		static bool TryLogWarning(const std::string& message);
		static bool TryLogError(const std::string& message);
		
		virtual void LogInfo(const std::string& message){}
		virtual void LogWarning(const std::string& message){}
		virtual void LogError(const std::string& message){}
		
	protected:
		static Logger* Get();
		
		virtual void Log(const std::string& message){}
		
		static bool isLoggingEnabled;
		static std::unique_ptr<Logger> currentLogger;

		std::string name;
	};
}
