#include <Shadow.h>

class Sandbox : public Shadow::Application {
public:
	
	Sandbox() {
		SH_DEBUGGER_INFO("Welcome to Shadow Engine");
	}
	~Sandbox() {
		SH_DEBUGGER_INFO("Closing Shadow Engine");
	}
};

Shadow::Application* Shadow::CreateApplication() {
	return new Sandbox();
}
