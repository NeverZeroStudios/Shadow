#pragma once


#include "Application.h"

#ifdef SHADOW_PLATFORM_WINDOWS

	#if defined _MSC_VER && defined _DEBUG // major and minor number elements of the compiler's version number. && ARE IN DEBUG MODE
	#include <crtdbg.h>
	//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__);
	#define ENABLE_LEAK_DETECT() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
	#else
	#define ENABLE_LEAK_DETECT()
	#endif


	extern ShadowEngine::Application* ShadowEngine::CreateApplication();

	// Entry Point for Windows Platform
	int main(int argc, char** argv) {
		
		ENABLE_LEAK_DETECT();
		_CrtSetBreakAlloc(-1);

		auto app = ShadowEngine::CreateApplication();
		app->Run();
		delete app;
	}

#endif 
