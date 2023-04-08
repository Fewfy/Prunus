#pragma once

#include "Prunus/Layer.h"

#include "Prunus/Events/MouseEvent.h"
#include "Prunus/Events/KeyEvent.h"
#include "Prunus/Events/ApplicationEvent.h"

namespace Prunus
{
	class PRUNUS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		//void OnKeyTypedEvent(KeyType)
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}