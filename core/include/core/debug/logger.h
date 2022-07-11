#pragma once

#include <cstdio>
#include <mutex>
#include <ctime>
#include <Windows.h>

class Logger
{
public:
	enum class LogPriority
	{
		Info, 
		Warn, 
		Error, 
		Critical
	};

private:
	LogPriority priority = LogPriority::Info;
	std::mutex logMutex;

public:
	static void SetPriority(LogPriority new_priority)
	{
		GetInstance().priority = new_priority;
	}

	static LogPriority GetPriority()
	{
		return GetInstance().priority;
	}

	template<typename... Args>
	static void LOG(const char* message, Args... args)
	{
		GetInstance().LogMessage(LogPriority::Info, 
			message, args...);
	}

	template<typename... Args>
	static void LOG(LogPriority priorityType, const char* message, 
		Args... args)
	{
		GetInstance().LogMessage(priorityType,
			message, args...);
	}

private:
	template<typename... Args>
	void LogMessage(LogPriority priorityType, const char* message, 
		Args... args)
	{
		auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		
		if (GetPriority() > priorityType)
			return;

		// Thread safe lock
		std::scoped_lock lock(logMutex);

		// Type of log priority
		switch (priorityType)
		{
		case LogPriority::Info:
			SetConsoleTextAttribute(hConsole, 15);
			printf("[INFO]\t");
			break;
		case LogPriority::Warn:
			SetConsoleTextAttribute(hConsole, 14);
			printf("[WARN]\t");
			break;
		case LogPriority::Error:
			SetConsoleTextAttribute(hConsole, 4);
			printf("[ERROR]\t");
			break;
		case LogPriority::Critical:
			SetConsoleTextAttribute(hConsole, 15 + 4 * 16);
			printf("[CRIT]\t");
			break;
		}

		// Print message
		std::printf(message, args...);
		std::printf("\t\n");
	}

private:
	Logger() {}

	Logger(const Logger&) = delete;
	Logger& operator= (const Logger&) = delete;

	~Logger()
	{
		
	}

	static Logger& GetInstance()
	{
		static Logger instance;

		return instance;
	}
};