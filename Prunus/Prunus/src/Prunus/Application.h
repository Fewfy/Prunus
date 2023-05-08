#pragma once
#include "Core.h"
#include "Window.h"
#include "Prunus/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Prunus/ImGui/ImGuiLayer.h"
#include "Prunus/Renderer/Shader.h"
#include "Prunus/Renderer/Buffer.h"
#include "Prunus/Renderer/VertexArray.h"
#include "Prunus/Renderer/OrthographicCamera.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;
	};

	Application* CreateApplication();
}