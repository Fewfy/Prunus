#include <Prunus.h>

class Sandbox : public Prunus::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox() {

	}
};

Prunus::Application* Prunus::CreateApplication()
{
	return new Sandbox();
}