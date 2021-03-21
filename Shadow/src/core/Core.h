#pragma once

#ifdef SHADOW_PLATFORM_WINDOWS
	
	#ifdef SHADOW_BUILD_DLL
		#define SHADOW_API __declspec(dllexport)
	#else
		#define SHADOW_API __declspec(dllimport)
	#endif

	//#define THROW_IF_FAILED(hr, msg) if(FAILED(hr)) { _com_error err(hr); std::wstringstream ss; ss << msg << std::endl << "Error Number: " << err.HRESULTToWCode(hr)<<std::endl<<"Error Description: " << err.ErrorMessage() << std::endl; SH_DEBUGGER_FATAL(ss.str().c_str()); }
	//#define TRY(good, msg) if(!good) { SH_DEBUGGER_FATAL(msg); return false; }

#endif


