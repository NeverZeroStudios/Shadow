#pragma once
#include "../Core.h"
#include "../../data_structures/Queue.h"
#include "../ShadowDebugger/Log.h"

namespace ShadowEngine {
	

	class SHADOW_API Keyboard
	{
	public:
		bool* keystates[104] = {0};

		bool IsKeyDown(int keycode) {
			return keystates[keycode];
		}

		Keyboard() {}
		~Keyboard() {}

	};
}

