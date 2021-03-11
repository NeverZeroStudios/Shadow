#include "Application.h"
#include "../ShadowDebugger/Log.h"
#include <comdef.h>
namespace ShadowEngine {

	Application::Application()
	{
		int width = 1280;
		int height = 720;
		int monitorWidth = GetSystemMetrics(SM_CXSCREEN);
		int monitorHeight = GetSystemMetrics(SM_CYSCREEN);

		int pos_x = monitorWidth / 2 - width / 2; // DEBUG used for 3840x1280 resolution
		int pos_y = monitorHeight / 2 - height / 2;

		std::stringstream ss;
		ss << "mWidth: " << monitorWidth << "\tmHeight: " << monitorHeight<< std::endl;
		SH_DEBUGGER_INFO(ss.str().c_str());

		if (!_window.Create(L"Shadow Engine Demo", WS_OVERLAPPEDWINDOW , 0, pos_x, pos_y, width, height))
		{
			std::stringstream ss;
			_com_error err(GetLastError());
			ss << "COULD NOT INITILIZE APPLICATION WINDOW\n" <<
				"Error Number: " << err.HRESULTToWCode(GetLastError()) << std::endl;
			SH_DEBUGGER_ERR(ss.str().c_str());
		}

		ShowWindow(_window.GetWindow(), SW_SHOW);
		UpdateWindow(_window.GetWindow());

		if (!_gfx.Init(_window)){
			
			std::stringstream ss;
			
			ss << "COULD NOT INITILIZE DIRECT X \n" <<
				"Error Number: " << GetLastError() << std::endl;
			
			SH_DEBUGGER_ERR(ss.str().c_str());
		}

		SH_DEBUGGER_INFO("Window Create Successfully");

		
	}

	Application::~Application()
	{
		_gfx.Cleanup();
	}

	int Application::Run()
	{
		while (true) {
			if (const auto eCode = _window.ProcessMessages()) {
				return *eCode;
			}
			ComposeFrame();
		}
	}

	void Application::ComposeFrame()
	{
		// GFX CLEAR BUFFER
		_gfx.ClearBuffer(.16f, .14f, .12f);
		// GFX DRAW
		_gfx.Draw();
		// GFX END FRAME
		_gfx.EndFrame();

	}
}
