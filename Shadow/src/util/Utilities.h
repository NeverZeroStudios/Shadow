#pragma once

#include "../core/Core.h"

// UTILITIES NOW INCLUDES IOSTREAM HEADERS
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace ShadowEngine {
	namespace Utilities {

		class SHADOW_API FileStructure {
		public:
			static std::wstring BuildFilePath(const wchar_t* filepath);
		private:
			static std::wstring GetExeFileNameW();
			static std::wstring GetExePathW();

			std::string GetBinaryString(int num, int bits) {

				std::string binary_str;

				for (int i = 0; i < bits; i++)
				{
					binary_str.append("0");
				}

				for (int i = bits - 1; i >= 0; i--)
				{
					if (num % 2 == 0) {
						binary_str[i] = '0';
					}
					else {
						binary_str[i] = '1';
					}
					num /= 2;
				}

				return binary_str;
			}

		};

	}
}