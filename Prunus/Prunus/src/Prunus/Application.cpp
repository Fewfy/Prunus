#include "pnpch.h"
#include "Application.h"
#include "Prunus/Events/ApplicationEvent.h"
#include "Prunus/Log.h"

namespace Prunus {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1200, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			PRUNUS_TRACE(e);
		}
		
	}
}