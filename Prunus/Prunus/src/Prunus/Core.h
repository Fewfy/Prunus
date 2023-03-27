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

#define BIT(x) (1 << x)