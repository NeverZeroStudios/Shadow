#include "KeyEvents.h"

namespace ShadowEngine {
	namespace Events {
	

#pragma region KeyEvents
	

		KeyEvent::KeyEvent(int kc) : _keycode(kc)
		{
		}

		const char* KeyEvent::GetClassificationToString()
		{
			return "Input | Keyboard";
		}

		int KeyEvent::GetKeyCode()
		{
			return _keycode;
		}

#pragma endregion

#pragma region Key Pressed Events

		std::string KeyPressedEvent::ToString()
		{
			std::stringstream __;
			__ << "Event Classification: " << GetClassificationToString() << std::endl <<
				"Event Type: " << GetTypeToString() << std::endl <<
				"Event Data: " << std::endl <<
				"KeyCode: " << GetKeyCode()<<"{"<<(char)GetKeyCode() <<"}" << "\t" << "Repeat Count: " << repeat_count << std::endl;
			return __.str();
		}

		KeyPressedEvent::KeyPressedEvent(int kc, int rp_count) : KeyEvent(kc), repeat_count(rp_count)
		{

		}

		const char* KeyPressedEvent::GetTypeToString()
		{
			return "Key Pressed Event";
		}

#pragma endregion

#pragma region Key Released Events

		KeyReleasedEvent::KeyReleasedEvent(int kc) : KeyEvent(kc)
		{
		}

		const char* KeyReleasedEvent::GetTypeToString()
		{
			return "Key Released Event";
		}

		std::string KeyReleasedEvent::ToString()
		{
			std::stringstream __;
			__ << "Event Classification: " << GetClassificationToString() << std::endl <<
				"Event Type: " << GetTypeToString() << std::endl <<
				"Event Data: " << std::endl <<
				"KeyCode: " << GetKeyCode() << "{" << (char)GetKeyCode() << "}" << std::endl;
			return __.str();
		}

#pragma endregion


	}
}