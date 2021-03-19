#include "Application.h"
#include <comdef.h>
namespace ShadowEngine {

	Application::Application()
	{
		int width = 1280;
		int height = 720;
		int monitorWidth = GetSystemMetrics(SM_CXSCREEN);
		int monitorHeight = GetSystemMetrics(SM_CYSCREEN);

		int pos_x = monitorWidth / 2 - width / 2; 
		int pos_y = monitorHeight / 2 - height / 2;

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

		// Init Input
		if (!_window.InitEventsQueue(_events)) {
			SH_DEBUGGER_ERR("Could Not Initilize Event Queue..");
		}
		if (!_window.InitKeyboard(this->Keyboard)) {
			SH_DEBUGGER_ERR("Could Not Initilize Keyboard..");
		}
		if (!_window.InitMouse(this->Mouse)) {

			SH_DEBUGGER_ERR("Could Not Initilize Keyboard..");
		}

		if (!_gfx.Init(_window)){
			
			std::stringstream ss;
			
			ss << "COULD NOT INITILIZE DIRECT X \n" <<
				"Error Number: " << GetLastError() << std::endl;
			
			SH_DEBUGGER_ERR(ss.str().c_str());
		}

		SH_DEBUGGER_LOG("Window Create Successfully");
	}

	Application::~Application()
	{
		_gfx.Cleanup();
	}

	void Application::ProcessEvents() {
		while (!_events.Empty()) {
			Events::Event* ev = _events.Peek()->data;
			SH_DEBUGGER_INFO(ev->ToString().c_str());
			// set the event to be handled 
			ev->Handled(true);
			_events.Dequeue();
		}
	}

	void Application::ComposeFrame()
	{
		// GFX CLEAR BUFFER
		_gfx.ClearBuffer(.0f, .0f, .0f);
		// GFX DRAW
		_gfx.Update(timer.Peek());
		// GFX END FRAME
		_gfx.EndFrame();
		

	}
}
