#include "Utilities.h"

namespace ShadowEngine {
	namespace Utilities {

		std::wstring FileStructure::BuildFilePath(const wchar_t* filepath)
		{
			std::wstringstream ss;
			ss << GetExePathW().c_str() << "\\" << filepath;
			return ss.str();
		}

		std::wstring FileStructure::GetExeFileNameW()
		{
			wchar_t buffer[MAX_PATH];
			GetModuleFileName(NULL, buffer, MAX_PATH);
			return std::wstring(buffer);
		}

		std::wstring FileStructure::GetExePathW()
		{
			std::wstring f = GetExeFileNameW();
			return f.substr(0, f.find_last_of(L"\\/"));
			
		}
		#define NOW  
		Timer::Timer()
		{
			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
			last = now;
		}

		Timer::~Timer()
		{
		}

		float Timer::Mark()
		{
			const auto old = last;
			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
			last = now;
			std::chrono::duration<float> frameTime = last - old;
			return frameTime.count();
		}

		float Timer::Peek()
		{
			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
			return std::chrono::duration<float>(now - last).count();
		}
	}
}



/*
	std::wstring GetExeFileName()
	{
		
	}

	std::wstring GetExePath()
	{
		
	}


*/