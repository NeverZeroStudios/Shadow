#include <Shadow.h>

class Sandbox : public ShadowEngine::Application {
public:
	Sandbox() {
		SHADOW_DEBUGGER::_INFO("Welcome to Shadow Engine");
	}
	~Sandbox() {}

};

ShadowEngine::Application* ShadowEngine::CreateApplication() {
	return new Sandbox();
}
