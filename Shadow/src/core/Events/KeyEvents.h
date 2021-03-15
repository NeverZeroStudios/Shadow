#pragma once
#include "Event.h"

namespace ShadowEngine { 
	namespace Events {

		class KeyEvent : public Events::Event {
			// Inherited via Event
		public:
			KeyEvent(int kc);

			virtual const char* GetClassificationToString() override;
			int GetKeyCode();

		protected:
			int _keycode;
		};

		class KeyPressedEvent : public KeyEvent {
		public:
			KeyPressedEvent(int kc, int rp_count);
			virtual const char* GetTypeToString() override;
			virtual std::string ToString() override;
		private:
			int repeat_count;
		};

		class KeyReleasedEvent : public KeyEvent {
		public:
			KeyReleasedEvent(int kc);
			virtual const char* GetTypeToString() override;
			virtual std::string ToString() override;
		};
		
	}
}

