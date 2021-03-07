#pragma once

#include "Core.h"

namespace ShadowEngine {

	class SHADOW_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// TBD in client
	Application* CreateApplication();
}



