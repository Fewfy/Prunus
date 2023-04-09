#pragma once

#include "Prunus/Input.h"

namespace Prunus
{
	class PRUNUS_API WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMousePressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePosImpl() override;
	};
}