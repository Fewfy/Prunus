#include "pnpch.h"
#include "OpenGLContext.h"
#include <glad/glad.h>

namespace Prunus
{
	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_WindowsHandle(window)
	{
		PRUNUS_ASSERT(m_WindowsHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowsHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PRUNUS_CORE_ASSERT(status, "Faield to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowsHandle);
	}
}