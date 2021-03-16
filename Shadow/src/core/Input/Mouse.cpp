#include "Mouse.h"

namespace ShadowEngine {
	namespace Input {
		
		Mouse::Mouse()
		{
		}
		
		Mouse::~Mouse()
		{
		}

		bool Mouse::IsButtonDown(int mouseButton)
		{
			return buttons[mouseButton];
		}

		MousePoint Mouse::Position()
		{
			return position;
		}

		void Mouse::Position(MousePoint point)
		{
			position = point;
		}
		
	}
}