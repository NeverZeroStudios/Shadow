#pragma once

#include "../Core.h"

#include "../Windows/Window.h"
#include "../ShadowDebugger/Log.h"
#include "../Graphics/Graphics.h"
#include "../Input/Keyboard.h"

// Event handling
#include "../../data_structures/Queue.h"
#include "../Events/Event.h"

namespace ShadowEngine {

	class SHADOW_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual int Run() = 0;
		void ComposeFrame();
		void ProcessEvents();
	protected:
		Window _window;
		Graphics _gfx;
		Input::Keyboard Keyboard;
		Input::Mouse Mouse;
		
		DataStructures::Queue<Events::Event*> _events;

	};

	Application* CreateApplication();
}



