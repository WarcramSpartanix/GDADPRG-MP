#include "pch.h"
#include "Debug.h"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Debug::m_Logger;

void Debug::Init()
{
#if DEBUG
    spdlog::set_pattern("%^[%T] %n: %v%$");
    m_Logger = spdlog::stdout_color_mt("APP");
    m_Logger->set_level(spdlog::level::trace);
#endif
}