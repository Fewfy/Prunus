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
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}