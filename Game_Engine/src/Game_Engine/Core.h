#pragma once

#ifdef PLATFORM_WINDOWS
	#ifdef BUILD_DLL
		#define GAME_ENGINE_API __declspec(dllexport)
	#else
		#define GAME_ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Game Engine only supports windows!
#endif

#define BIT(x) (1<<x)