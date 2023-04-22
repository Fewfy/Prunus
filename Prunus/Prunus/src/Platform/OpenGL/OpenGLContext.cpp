#include "pnpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

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

		PRUNUS_CORE_INFO("OpenGL Info:");
		//std::string vendor((char*)glGetString(GL_VENDOR));
		PRUNUS_CORE_INFO("    Vendor: {0}", (char*)glGetString(GL_VENDOR));
		PRUNUS_CORE_INFO("    Renderer: {0}", (char*)glGetString(GL_RENDERER));
		PRUNUS_CORE_INFO("    Version: {0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowsHandle);
	}
}