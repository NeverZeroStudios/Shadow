#pragma once

#include "../Core.h"

#include "../ShadowDebugger/Log.h"

#include "../Windows/Window.h"


#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"

// Event handling
#include "../Events/Event.h"
#include "../../util/Utilities.h"
#include "../Graphics2D/Graphics2D.h"

namespace ShadowEngine {

	class SHADOW_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		virtual int Run() = 0;

	protected:
		Window window;

		Input::Keyboard Keyboard();
		Input::Mouse Mouse();

		void ComposeFrame();
		void ProcessEvents();

	private:
		bool Init();
	
	};

	Application* CreateApplication();
}



