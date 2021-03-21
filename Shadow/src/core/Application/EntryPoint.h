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

	//// Entry Point for Windows Platform
	//int main(int argc, char** argv) {
	//	
	//	ENABLE_LEAK_DETECT();
	//	_CrtSetBreakAlloc(-1);

	//	auto app = ShadowEngine::CreateApplication();
	//	app->Run();
	//	delete app;
	//}
    int WINAPI WinMain(
            HINSTANCE /* hInstance */,
            HINSTANCE /* hPrevInstance */,
            LPSTR /* lpCmdLine */,
            int /* nCmdShow */
        )
    {
        // Use HeapSetInformation to specify that the process should
        // terminate if the heap manager detects an error in any heap used
        // by the process.
        // The return value is ignored, because we want to continue running in the
        // unlikely event that HeapSetInformation fails.
        HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

        if (SUCCEEDED(CoInitialize(NULL)))
        {
            {
                auto app = ShadowEngine::CreateApplication();
                app->Run();
                delete app;
            }
            CoUninitialize();
        }

        return 0;
    }
#endif 
