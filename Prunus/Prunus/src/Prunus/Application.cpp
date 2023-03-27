#include "Application.h"
#include <iostream>

#include "Prunus/Events/ApplicationEvent.h"
#include "Prunus/Log.h"

namespace Prunus {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1200, 720);
		PRUNUS_TRACE(e);
	}
}