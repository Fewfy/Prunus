#include "pnpch.h"
#include "Application.h"

#include "Prunus/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Prunus {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Prunus::ShaderDataType::None:			return GL_FLOAT;
			case Prunus::ShaderDataType::Float:		return GL_FLOAT;
			case Prunus::ShaderDataType::Float2:	return GL_FLOAT;
			case Prunus::ShaderDataType::Float3:	return GL_FLOAT;
			case Prunus::ShaderDataType::Float4:	return GL_FLOAT;
			case Prunus::ShaderDataType::Mat3:		return GL_FLOAT;
			case Prunus::ShaderDataType::Mat4:		return GL_FLOAT;
			case Prunus::ShaderDataType::Int:		return GL_INT; 
			case Prunus::ShaderDataType::Int2:		return GL_INT; 
			case Prunus::ShaderDataType::Int3:		return GL_INT; 
			case Prunus::ShaderDataType::Int4:		return GL_INT; 
			case Prunus::ShaderDataType::Bool:		return GL_BOOL; 
		}

		PRUNUS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application() 
	{
		PRUNUS_CORE_ASSERT(!s_Instance, "Application already exist");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,	.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f,	1.0f, 0.0f, 1.0f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		uint32_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			auto count = element.GetElementCount();
			auto t = ShaderDataTypeToOpenGLBaseType(element.Type);
			auto stride = layout.GetStride();
			glVertexAttribPointer(index, 
				element.GetElementCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(const void*)element.Offset);
			index++;
		}

		uint32_t indices[3] = { 0, 1, 2 };
		
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
				v_Color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application() {

	}

	void Application::Run() 
	{
		while (m_Running)
		{
			glClearColor(0.2f, 0.2f, 0.2f, 0);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			--it;
			(*it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		m_Running = false;
		return true;
	}
}