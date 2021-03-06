#include "rapch.h"
#include "RoboArena/log.h"

std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_Logger = spdlog::stdout_color_mt("RoboArena");
    s_Logger->set_level(spdlog::level::trace);
    s_Logger->critical("RoboArena v0.1");
}
