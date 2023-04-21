#pragma once
#include "Prunus/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Prunus
{
	class PRUNUS_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;

		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowsHandle;
	};
}