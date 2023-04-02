#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Prunus/LayerStack.h"
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
		void PoshOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowClosedEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}