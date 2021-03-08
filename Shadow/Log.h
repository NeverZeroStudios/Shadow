#pragma once
#include "Core.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <iomanip>

#include <sstream>

#include <ctime>

#define SHADOW_DEBUGGER ShadowEngine::Debug

namespace ShadowEngine{
	namespace Debug {

		#define NONE	0b0000'0000				
		#define RIGHT	0b0000'0001				
		#define LEFT	0b0000'0010				
		#define CENTER  0b0000'0011				

		enum LogColor
		{
			Black = 0,
			DarkBlue = FOREGROUND_BLUE,
			DarkGreen = FOREGROUND_GREEN,
			DarkCyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
			DarkRed = FOREGROUND_RED,
			DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE,
			DarkYellow = FOREGROUND_RED | FOREGROUND_GREEN,
			Gray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			DarkGray = FOREGROUND_INTENSITY,
			Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
			Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
			Magenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
			White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		};

		class SHADOW_API Logger {

		public:
			static void Log(const char* msg, LogColor fg_color, LogColor bg_color=LogColor::Black, WORD format = LEFT);

		private:
			static WORD BackgroundColor();
			static WORD ForegroundColor();

			static void ForegroundColor(WORD color);
			static void BackgroundColor(WORD color);

			static void ResetColors();

			static HANDLE hOuput;

		};
	
	}

// PRE-FORMATTED LOG STATEMENTS
// --------------------------------
#ifdef SE_BUILD_DLL
#define _INFO(msg)	Logger::Log(msg, SHADOW_DEBUGGER::LogColor::White)	
#define _LOG(msg)	Logger::Log(msg, SHADOW_DEBUGGER::LogColor::Green) 
#define _TRACE(msg)	Logger::Log(msg, SHADOW_DEBUGGER::LogColor::Yellow)
#define _ERROR(msg)	Logger::Log(msg, SHADOW_DEBUGGER::LogColor::DarkRed)
#define _FATAL(msg)	Logger::Log(msg, SHADOW_DEBUGGER::LogColor::Red)
#else
#define _INFO(msg)	Logger::Log(msg, SHADOW_DEBUGGER::LogColor::White)	
#define _LOG(msg)	Logger::Log(msg, SHADOW_DEBUGGER::LogColor::Green) 
#define _TRACE(msg)	Logger::Log(msg, SHADOW_DEBUGGER::LogColor::Yellow)
#define _ERROR(msg)	Logger::Log(msg, SHADOW_DEBUGGER::LogColor::DarkRed)
#define _FATAL(msg)	Logger::Log(msg, SHADOW_DEBUGGER::LogColor::Red)	
#endif
}