#pragma once

#ifdef PRUNUS_PLATFORM_WINDOWS
	#ifdef PRUNUS_BUILD_DLL
		#define PRUNUS_API __declspec(dllexport)
	#else
		#define PRUNUS_API __declspec(dllimport)
	#endif
#else
#error Only support Windows!
#endif

#ifdef PRUNUS_ENABLE_ASSERTS
	#define PRUNUS_ASSERT(x, ...){ if(!(x)){ PRUNUS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define PRUNUS_CORE_ASSERT(x, ...){if(!(x)){ PRUNUS_CORE_ERROR("Assertion Failed:  {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define PRUNUS_ASSERT(x, ...)
	#define PRUNUS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)