#include "Application.h"
#include <comdef.h>


namespace ShadowEngine {

	Application::Application()
	{
		if (!Init())
			SH_DEBUGGER_FATAL("Could Not Initilize Shadow Engine");
		else
			SH_DEBUGGER_LOG("Window Create Successfully");

	}

	Application::~Application()
	{

	}

	bool Application::Init()
	{

		int width = 1280;
		int height = 720;
		int monitorWidth = GetSystemMetrics(SM_CXSCREEN);
		int monitorHeight = GetSystemMetrics(SM_CYSCREEN);

		int pos_x = monitorWidth / 2 - width / 2;
		int pos_y = monitorHeight / 2 - height / 2;

		
		if (!window.Create(L"Shadow Engine GUI Demo", WS_OVERLAPPEDWINDOW, 0, pos_x, pos_y, width, height)) {
			std::wstringstream ss;
			SH_DEBUGGER_ERR("COULD NOT INITILIZE DEMO WINDOW");
			return false;
		}

		ShowWindow(window.GetWindow(), SW_SHOW);
		UpdateWindow(window.GetWindow());

		return true;
	}

	void Application::ProcessEvents() {
		while (!window.GetEvents().Empty()) {
			Events::Event* ev = window.GetEvents().Peek()->data;
			SH_DEBUGGER_INFO(ev->ToString().c_str());
			// set the event to be handled 
			ev->Handled(true);
			window.GetEvents().Dequeue();
		}
	}

	Input::Keyboard Application::Keyboard()
	{
		return window.GetKeyboard();
	}

	Input::Mouse Application::Mouse()
	{
		return window.GetMouse();
	}

	void Application::ComposeFrame()
	{
	
	}

	
}
