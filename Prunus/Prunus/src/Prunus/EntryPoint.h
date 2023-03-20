#pragma once

#ifdef PRUNUS_PLATFORM_WINDOWS
extern Prunus::Application* Prunus::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Prunus::CreateApplication();
	app->Run();
	delete app;
}

#endif