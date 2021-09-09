#pragma once

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Log
{
public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};

// log macros
#ifdef false
    #define TRACE(...) ::Log::GetLogger()->trace(__VA_ARGS__)
    #define INFO(...) ::Log::GetLogger()->info(__VA_ARGS__)
    #define WARN(...) ::Log::GetLogger()->warn(__VA_ARGS__)
    #define ERROR(...) ::Log::GetLogger()->error(__VA_ARGS__)
    #define FATAL(...) ::Log::GetLogger()->fatal(__VA_ARGS__)
#else
    #define TRACE(...)
    #define INFO(...)
    #define WARN(...)
    #define ERROR(...)
    #define FATAL(...)
#endif
