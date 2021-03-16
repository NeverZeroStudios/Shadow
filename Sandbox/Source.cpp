#include <Shadow.h>
#include <iostream>
#include <sstream>
class Sandbox : public Shadow::Application {
public:
	
	Sandbox() {
		SH_DEBUGGER_INFO("Welcome to Shadow Engine");
	}
	~Sandbox() {
		SH_DEBUGGER_INFO("Closing Shadow Engine");
	}

	virtual int Run() override {
		while (true) {
			// Process Messages 
			if (const auto eCode = _window.ProcessMessages()) {
				return *eCode;
			}
			// Process Events
			ProcessEvents();
			// Draw Graphics
			ComposeFrame();



			// Tests
			if (Keyboard.IsKeyDown(VK_A) || Keyboard.IsKeyDown(VK_W)) {
			

					SH_DEBUGGER_TRACE("Pressed a Key client side");
			}
			if (Keyboard.IsKeyDown(VK_SPACE)) {
				SH_DEBUGGER_TRACE("Pressed a Key client side");
			}
			if (Mouse.IsButtonDown(0)) {
				std::stringstream ss;
				ss << "LMB down" << std::endl <<
					"x: " << Mouse.Position().x << "\ty " << Mouse.Position().y << std::endl;
				SH_DEBUGGER_TRACE(ss.str().c_str());
			}
			if (Mouse.IsButtonDown(2)) {
				SH_DEBUGGER_TRACE("RMB IS DOWN on the client side");
			}
		}
	}

};

Shadow::Application* Shadow::CreateApplication() {
	return new Sandbox();
}
