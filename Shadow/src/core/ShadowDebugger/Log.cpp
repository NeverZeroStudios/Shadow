#include "Log.h"
#include <chrono>

namespace ShadowEngine {

	namespace Debug {
		
		HANDLE Logger::hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
		
		void Logger::Log(const char* message, LogColor fg_color, LogColor bg_color, const char* sender)
		{	
			time_t cur_time = time(0);
			tm ts;
			localtime_s(&ts, &cur_time);

			int yr =  ts.tm_year + 1900;
			int mo =  ts.tm_mon + 1;
			int day = ts.tm_mday;
			int hr =  ts.tm_hour;
			int min = ts.tm_min;
			int sec = ts.tm_sec;
			
			ResetColors();
			std::stringstream time_stamp;
			time_stamp << "[" << day << "/" << mo << "/" << yr << " " << hr << ":" << min << ":" << sec << "]";
			std::cout << time_stamp.str() << std::endl;
			

			ForegroundColor(fg_color);
			BackgroundColor(bg_color);
			std::wstringstream ss;
			ss  << sender << ": " << message << std::endl;
			OutputDebugStringW(ss.str().c_str());

			
			ResetColors();
		}

		void Logger::Log(const wchar_t* msg, LogColor fg_color, LogColor bg_color, const wchar_t* sender)
		{
			time_t cur_time = time(0);
			tm ts;
			localtime_s(&ts, &cur_time);

			int yr = ts.tm_year + 1900;
			int mo = ts.tm_mon + 1;
			int day = ts.tm_mday;
			int hr = ts.tm_hour;
			int min = ts.tm_min;
			int sec = ts.tm_sec;

			ResetColors();
			std::stringstream time_stamp;
			time_stamp << "[" << day << "/" << mo << "/" << yr << " " << hr << ":" << min << ":" << sec << "]";
			std::cout << time_stamp.str() << std::endl;


			ForegroundColor(fg_color);
			BackgroundColor(bg_color);
			std::wstringstream ss;
			ss << sender <<  ": " << msg << std::endl;
			OutputDebugStringW(ss.str().c_str());

			ResetColors();
		}

		#pragma region COLOR MANAGEMENT

		WORD Logger::BackgroundColor()
		{
			CONSOLE_SCREEN_BUFFER_INFO info;
			GetConsoleScreenBufferInfo(hOuput, &info);
			return (info.wAttributes & 0xF0) >> 4;
		}

		WORD Logger::ForegroundColor()
		{
			CONSOLE_SCREEN_BUFFER_INFO info;
			GetConsoleScreenBufferInfo(hOuput, &info);
			return info.wAttributes & 0x0f;
		}

		void Logger::ForegroundColor(WORD color)
		{
			CONSOLE_SCREEN_BUFFER_INFO info;
			GetConsoleScreenBufferInfo(hOuput, &info);
			SetConsoleTextAttribute(hOuput, info.wAttributes & 0xF0 | color);
		}

		void Logger::BackgroundColor(WORD color)
		{
			CONSOLE_SCREEN_BUFFER_INFO info;
			GetConsoleScreenBufferInfo(hOuput, &info);
			SetConsoleTextAttribute(hOuput, info.wAttributes & 0x0F | color << 4);

		}

		void Logger::ResetColors()
		{
			ForegroundColor(LogColor::Gray);
			BackgroundColor(LogColor::Black);
		}

		#pragma endregion
	}
}