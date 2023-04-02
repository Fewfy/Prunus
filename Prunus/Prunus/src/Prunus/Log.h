#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Prunus{
	class Log
	{
	public:
		PRUNUS_API static void Init();

		PRUNUS_API inline static std::shared_ptr<spdlog::logger>& GetCoreLogger();
		PRUNUS_API inline static std::shared_ptr<spdlog::logger>& GetClientLogger();
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define PRUNUS_CORE_ERROR(...)	::Prunus::Log::GetCoreLogger() ->error(__VA_ARGS__)
#define PRUNUS_CORE_WARN(...)	::Prunus::Log::GetCoreLogger() ->warn(__VA_ARGS__)
#define PRUNUS_CORE_INFO(...)	::Prunus::Log::GetCoreLogger() ->info(__VA_ARGS__)
#define PRUNUS_CORE_TRACE(...)	::Prunus::Log::GetCoreLogger() ->trace(__VA_ARGS__)
								  
#define PRUNUS_ERROR(...)		::Prunus::Log::GetClientLogger() ->error(__VA_ARGS__)
#define PRUNUS_WARN(...)		::Prunus::Log::GetClientLogger() ->warn(__VA_ARGS__)
#define PRUNUS_INFO(...)		::Prunus::Log::GetClientLogger() ->info(__VA_ARGS__)
#define PRUNUS_TRACE(...)		::Prunus::Log::GetClientLogger() ->trace(__VA_ARGS__)
