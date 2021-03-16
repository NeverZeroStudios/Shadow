#pragma once
#include "../Core.h"

namespace ShadowEngine {
	namespace Input {
		struct SHADOW_API MousePoint {
				int x;
				int y;
		};

		class SHADOW_API Mouse
		{
		public:
			Mouse();
			~Mouse();
			bool buttons[5]{ 0 };

			bool IsButtonDown(int mouseButton);

			MousePoint Position();
			void Position(MousePoint point);

		private:
			MousePoint position;
		};
	}
}

