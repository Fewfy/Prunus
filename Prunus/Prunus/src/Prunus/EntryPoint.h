#pragma once

#ifdef PRUNUS_PLATFORM_WINDOWS
extern Prunus::Application* Prunus::CreateApplication();

int main(int argc, char** argv)
{
	Prunus::Log::Init();
	PRUNUS_CORE_WARN("Initialized Log!");
	PRUNUS_INFO("Hello PreMake!!");

	
	auto app = Prunus::CreateApplication();
	app->Run();
	delete app;
}

#endif