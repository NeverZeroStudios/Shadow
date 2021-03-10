#pragma once

#include "../Core.h"
#include "../ShadowDebugger/Log.h"
#include "../Graphics/Graphics.h"

#include <wrl/client.h>

namespace ShadowEngine {

	class SHADOW_API Application
	{
	public:
		Application();
		virtual ~Application();




		int Run();
	private:
		Window _window;
		Graphics _gfx;
	};

	Application* CreateApplication();
}



