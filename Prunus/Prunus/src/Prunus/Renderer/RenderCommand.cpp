#include "pnpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Prunus
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}