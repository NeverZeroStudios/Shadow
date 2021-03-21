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
		
	}
}