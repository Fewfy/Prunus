#include <pnpch.h>
#include <Prunus.h>

class ExampleLayer : public Prunus::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		PRUNUS_INFO("ExampleLayer::Update");
	}

	void OnEvent(Prunus::Event& event) override
	{
		PRUNUS_TRACE("{0}", event);
	}
};

class Sandbox : public Prunus::Application
{
public:
	Sandbox()
	{
		Application::PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Prunus::Application* Prunus::CreateApplication()
{
	return new Sandbox();
}