#include "pnpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Prunus
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
				PRUNUS_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLVertexArray();
		}

		PRUNUS_ASSERT(false, "Unknown API!");
		return nullptr;
	}
}