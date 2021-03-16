#pragma once
#include "../Input/Mouse.h"
#include "Event.h"

namespace ShadowEngine {
	namespace Events {
		
	
		enum MOUSE_BUTTON {
			LEFT, 
			MIDDLE,
			RIGHT, 
		};
		class MouseEvent : public Events::Event
		{
		public:
			MouseEvent(int x, int y);
			// Inherited via Event
			virtual const char* GetClassificationToString() override;

			virtual Input::MousePoint GetPosition(); 
		private:
			Input::MousePoint position;

		};

		class MouseClickEvent : public MouseEvent {
		public:
			MouseClickEvent(int x, int y, MOUSE_BUTTON btn) : MouseEvent(x, y), pressed(btn) {}

			virtual std::string ToString() override;
			virtual const char* GetTypeToString() override;
		private:
			MOUSE_BUTTON pressed;

		};

		class MouseReleasedEvent : public MouseEvent {
		public:
			MouseReleasedEvent(int x, int y, MOUSE_BUTTON btn) : MouseEvent(x, y), pressed(btn) {}

			virtual std::string ToString() override;
			virtual const char* GetTypeToString() override;
		private:
			MOUSE_BUTTON pressed;

		};

		class MouseMovedEvent : public MouseEvent {
		public:
			MouseMovedEvent(int x, int y);
			virtual std::string ToString() override;
			virtual const char* GetTypeToString() override;
		
		};

		// mouse click / release
		// mouse scroll
		// mouse move
	}
}

