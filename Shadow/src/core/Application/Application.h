#pragma once

#include "../Core.h"
#include "../ShadowDebugger/Log.h"

namespace ShadowEngine {

	class SHADOW_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	Application* CreateApplication();
}



