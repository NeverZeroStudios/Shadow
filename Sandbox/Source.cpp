#include <Shadow.h>

class Sandbox : public Shadow::Application {
public:
	Sandbox(int width, int height) {
		SH_DEBUGGER_INFO("Welcome to Shadow Engine");
	}
	Sandbox() {
		SH_DEBUGGER_INFO("Welcome to Shadow Engine");
	}
	~Sandbox() {
		SH_DEBUGGER_INFO("Closing Shadow Engine");
	}
};

Shadow::Application* Shadow::CreateApplication() {
	return new Sandbox(1280, 720);
}
