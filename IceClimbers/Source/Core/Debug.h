#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Debug
{
public:
	static void Init();

	/*---------------------------- LOGGER -----------------------------*/
	#if DEBUG
	template <typename... Args>
    static void Log(const char* formattedMessage, const Args&... args)
	{
		m_Logger->debug(formattedMessage, args...);
	}

	template <typename... Args>
    static void Warn(const char* formattedMessage, const Args&... args)
	{
		m_Logger->warn(formattedMessage, args...);
	}

	template <typename... Args>
    static void Error(const char* formattedMessage, const Args&... args)
	{
		m_Logger->error(formattedMessage, args...);
	}

	template <typename... Args>
    static void Critical(const char* formattedMessage, const Args&... args)
	{
		m_Logger->critical(formattedMessage, args...);
	}
#else
	template <typename... Args>
    static void Log(const char* formattedMessage, const Args&... args)
	{
	}

	template <typename... Args>
    static void Warn(const char* formattedMessage, const Args&... args)
	{
	}

	template <typename... Args>
    static void Error(const char* formattedMessage, const Args&... args)
	{
	}

	template <typename... Args>
    static void Critical(const char* formattedMessage, const Args&... args)
	{
	}
#endif
private:
	static std::shared_ptr<spdlog::logger> m_Logger;
};

#ifdef ENABLE_ASSERTS
#define ASSERT(expected, errorMessage, ...) {							\
	if(!(expected))														\
	{																	\
		Debug::Error((std::string("Assertion Failed: ") +				\
		std::string(errorMessage)).c_str(),								\
		__VA_ARGS__);													\
		__debugbreak();													\
	}																	\
}																		
#else
#define ASSERT(expected, errorMessage, ...)
#endif