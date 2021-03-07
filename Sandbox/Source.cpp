#include <Shadow.h>

class Sandbox : public ShadowEngine::Application {
public:
	Sandbox() {}
	~Sandbox() {}

};

ShadowEngine::Application* ShadowEngine::CreateApplication() {
	return new Sandbox();
}
