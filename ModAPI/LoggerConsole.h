#pragma once
#include <string>

#include "Bone.h"
#include "Logger.h"

namespace ModAPI::Logging
{
	class LoggerConsole : public Logger
	{
	public:
		LoggerConsole(const std::string& loggerName);
		LoggerConsole(const LoggerConsole& loggerToCopy) = default;
		LoggerConsole(LoggerConsole&& loggerToMove) noexcept;
		~LoggerConsole() override;

		LoggerConsole& operator=(const LoggerConsole& loggerToCopy) = default;
		LoggerConsole& operator=(LoggerConsole&& loggerToMove) noexcept;

		void LogInfo(const std::string& message) override;
		void LogWarning(const std::string& message) override;
		void LogError(const std::string& message) override;

	protected:
		void Log(const std::string& message) override;
		void AllocateConsole() const;

		int currentTextColorId {15};
	};
}
