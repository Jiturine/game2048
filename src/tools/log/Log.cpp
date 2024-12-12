#include "Log.h"

std::shared_ptr<spdlog::logger> Log::logger;

void Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	logger = spdlog::stdout_color_mt("GAME2048");
	logger->set_level(spdlog::level::trace);
}