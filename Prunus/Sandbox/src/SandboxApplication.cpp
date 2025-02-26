#include <pnpch.h>
#include <Prunus.h>

#include "glm/gtx/transform.hpp"
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Prunus::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f), m_CameraPosition(0), m_SquarePosition(0.0f)
	{
		{
			m_VertexArray.reset(Prunus::VertexArray::Create());
			float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				0.5f, -0.5f, 0.0f,	0.2f, 0.3f, 0.8f, 1.0f,
				0.0f, 0.5f, 0.0f,	0.8f, 0.8f, 0.2f, 1.0f
			};

			std::shared_ptr<Prunus::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(Prunus::VertexBuffer::Create(vertices, sizeof(vertices)));

			Prunus::BufferLayout layout = {
				{Prunus::ShaderDataType::Float3, "a_Position" },
				{Prunus::ShaderDataType::Float4, "a_Color" }
			};

			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			uint32_t indices[3] = { 0, 1, 2 };

			std::shared_ptr<Prunus::IndexBuffer> indexBuffer;
			indexBuffer.reset(Prunus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			m_VertexArray->SetIndexBuffer(indexBuffer);
		}

		if (true)
		{
			m_SquareVA.reset(Prunus::VertexArray::Create());

			float squareVertices[3 * 4] = {
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f
			};

			std::shared_ptr<Prunus::VertexBuffer> squareVB;
			squareVB.reset(Prunus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
			squareVB->SetLayout({
				{Prunus::ShaderDataType::Float3, "a_Position" }
				});

			m_SquareVA->AddVertexBuffer(squareVB);

			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

			std::shared_ptr<Prunus::IndexBuffer> squareIB;
			squareIB.reset(Prunus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
			m_SquareVA->SetIndexBuffer(squareIB);
		}

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader.reset(Prunus::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_BlueShader.reset(Prunus::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Prunus::Timestep ts) override
	{
		PRUNUS_INFO("Delta time: {0}", ts.GetSeconds());

		if(Prunus::Input::IsKeyPressed(PRUNUS_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}

		if (Prunus::Input::IsKeyPressed(PRUNUS_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (Prunus::Input::IsKeyPressed(PRUNUS_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}

		if (Prunus::Input::IsKeyPressed(PRUNUS_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if(Prunus::Input::IsKeyPressed(PRUNUS_KEY_A))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		if(Prunus::Input::IsKeyPressed(PRUNUS_KEY_D))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		if (Prunus::Input::IsKeyPressed(PRUNUS_KEY_J))
		{
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		}

		if (Prunus::Input::IsKeyPressed(PRUNUS_KEY_L))
		{
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		}

		if (Prunus::Input::IsKeyPressed(PRUNUS_KEY_I))
		{
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		}

		if (Prunus::Input::IsKeyPressed(PRUNUS_KEY_K))
		{
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;
		}

		Prunus::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0 });
		Prunus::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		
		Prunus::Renderer::BeginScene(m_Camera);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);

		std::dynamic_pointer_cast<Prunus::OpenGLShader>(m_BlueShader)->Bind();
		std::dynamic_pointer_cast<Prunus::OpenGLShader>(m_BlueShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for(int y = 0;y < 20; y++)
		{
			for(int x = 0;x < 20;x ++)
			{
				glm::vec3 pos(x * 0.11f, y *0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Prunus::Renderer::Submit(m_SquareVA, m_BlueShader, transform);
			}
		}
		Prunus::Renderer::Submit(m_VertexArray, m_Shader);

		Prunus::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Prunus::Event& event) override
	{
		Prunus::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Prunus::KeyPressedEvent>(PRUNUS_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
	}

	bool OnKeyPressed(Prunus::KeyPressedEvent& event)
	{
		return false;
	}

private:
	std::shared_ptr<Prunus::Shader> m_Shader;
	std::shared_ptr<Prunus::VertexArray> m_VertexArray;

	std::shared_ptr<Prunus::Shader> m_BlueShader;
	std::shared_ptr<Prunus::VertexArray> m_SquareVA;

	Prunus::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;

	glm::vec3 m_SquareColor = { 0.5, 0.2, 0.3 };
};

class Sandbox : public Prunus::Application
{
public:
	Sandbox()
	{
		Application::PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Prunus::Application* Prunus::CreateApplication()
{
	return new Sandbox();
}