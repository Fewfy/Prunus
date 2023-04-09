#include "pnpch.h"
#include "WindowsInput.h" 
#include "Prunus/Application.h"
#include <GLFW/glfw3.h>

namespace Prunus
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto app = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(app, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMousePressedImpl(int button)
	{
		auto app = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int status = glfwGetKey(app, button);

		return status == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto app = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(app, &x, &y);

		return { (float)x, (float)y };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[x,y] = GetMousePosImpl();

		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto[x, y] = GetMousePosImpl();

		return y;
	}
}