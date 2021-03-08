#pragma once
#include "Log.h"

#ifdef SE_PLATFORM_WINDOWS

	extern ShadowEngine::Application* ShadowEngine::CreateApplication();


int main(int argc, char** argv) {

	auto app = ShadowEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif 
