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
		if (Prunus::Input::IsKeyPressed(PRUNUS_KEY_SPACE))
			PRUNUS_INFO("Space key is pressed");
	}

	void OnEvent(Prunus::Event& event) override
	{
		//PRUNUS_TRACE("{0}", event);
	}
};

class Sandbox : public Prunus::Application
{
public:
	Sandbox()
	{
		Application::PushLayer(new ExampleLayer());
		Application::PushOverlay(new Prunus::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Prunus::Application* Prunus::CreateApplication()
{
	return new Sandbox();
}