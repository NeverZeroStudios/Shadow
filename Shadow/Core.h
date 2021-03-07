#pragma once

#ifdef SE_PLATFORM_WINDOWS
	#ifdef SE_BUILD_DLL
		#define SHADOW_API __declspec(dllexport)
	#else
		#define SHADOW_API __declspec(dllimport)
	#endif
#endif