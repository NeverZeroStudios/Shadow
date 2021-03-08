#pragma once
#include "../ShadowDebugger/Log.h"

#ifdef SHADOW_PLATFORM_WINDOWS

	extern ShadowEngine::Application* ShadowEngine::CreateApplication();

	// Entry Point for Windows Platform
	int main(int argc, char** argv) {
		auto app = ShadowEngine::CreateApplication();
		app->Run();
		delete app;
	}

#endif 
