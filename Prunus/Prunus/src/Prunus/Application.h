#pragma once
#include "Core.h"
#include "Window.h"
#include "Prunus/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Prunus {
	class PRUNUS_API Application
	{
	public:
		Application();
		~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get(){ return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowClosedEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}