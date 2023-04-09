#pragma once

#include "Prunus/Core.h"

namespace Prunus
{
	class PRUNUS_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMousePressed(int button) { return s_Instance->IsMousePressedImpl(button); }
		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		inline static bool GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static bool GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMousePressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
	private:
		static Input* s_Instance;
	};
}
