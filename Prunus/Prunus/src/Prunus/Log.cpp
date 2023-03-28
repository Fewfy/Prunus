#include "pnpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Prunus {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("PRUNUS");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	inline std::shared_ptr<spdlog::logger>& Log::GetClientLogger() { return s_ClientLogger; }
	inline std::shared_ptr<spdlog::logger>& Log::GetCoreLogger() { return s_CoreLogger; }
}