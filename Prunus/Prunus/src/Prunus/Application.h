#pragma once
#include "Core.h"
#include "Window.h"
#include "Prunus/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Prunus/ImGui/ImGuiLayer.h"
#include "Prunus/Renderer/Shader.h"
#include "Prunus/Renderer/Buffer.h"

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;

		unsigned int m_VertexArray;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	Application* CreateApplication();
}