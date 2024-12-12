#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Log
{
  public:
	static void Init();
	static std::shared_ptr<spdlog::logger> logger;
};

#define LOG_TRACE(...) Log::logger->trace(__VA_ARGS__)
#define LOG_INFO(...) Log::logger->info(__VA_ARGS__)
#define LOG_WARN(...) Log::logger->warn(__VA_ARGS__)
#define LOG_ERROR(...) Log::logger->error(__VA_ARGS__)
#define LOG_FATAL(...) Log::logger->fatal(__VA_ARGS__)