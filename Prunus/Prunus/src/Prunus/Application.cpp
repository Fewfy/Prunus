#include "pnpch.h"
#include "Application.h"
#include "Prunus/Events/ApplicationEvent.h"
#include "Prunus/Log.h"

namespace Prunus {
	Application::Application() 
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() 
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}