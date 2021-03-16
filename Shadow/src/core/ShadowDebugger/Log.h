#pragma once
#include "../Core.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <iomanip>

#include <sstream>

#include <ctime>


namespace ShadowEngine{
	namespace Debug {

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
			static void Log(const char* msg, LogColor fg_color, LogColor bg_color = LogColor::Black,  const char* sender = "ENGINE");
			static void Log(const wchar_t* msg, LogColor fg_color, LogColor bg_color=LogColor::Black, const wchar_t* sender = L"ENGINE");

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
#ifdef SHADOW_BUILD_DLL
#define SH_DEBUGGER_INFO(msg)		Debug::Logger::Log(msg, Debug::LogColor::White)	
#define SH_DEBUGGER_LOG(msg)		Debug::Logger::Log(msg, Debug::LogColor::Green) 
#define SH_DEBUGGER_TRACE(msg)		Debug::Logger::Log(msg, Debug::LogColor::Yellow)
#define SH_DEBUGGER_ERR(msg)		Debug::Logger::Log(msg, Debug::LogColor::DarkRed)
#define SH_DEBUGGER_FATAL(msg)		Debug::Logger::Log(msg, Debug::LogColor::Red)
#else
#define SH_DEBUGGER_INFO(msg)		ShadowDebugger::Logger::Log(msg, ShadowDebugger::LogColor::White, ShadowDebugger::LogColor::Black, "CLIENT")	
#define SH_DEBUGGER_LOG(msg)		ShadowDebugger::Logger::Log(msg, ShadowDebugger::LogColor::Green, ShadowDebugger::LogColor::Black, "CLIENT") 
#define SH_DEBUGGER_TRACE(msg)		ShadowDebugger::Logger::Log(msg, ShadowDebugger::LogColor::Yellow, ShadowDebugger::LogColor::Black, "CLIENT")
#define SH_DEBUGGER_ERR(msg)		ShadowDebugger::Logger::Log(msg, ShadowDebugger::LogColor::DarkRed, ShadowDebugger::LogColor::Black, "CLIENT")
#define SH_DEBUGGER_FATAL(msg)		ShadowDebugger::Logger::Log(msg, ShadowDebugger::LogColor::Red, ShadowDebugger::LogColor::Black, "CLIENT")	
#endif
}