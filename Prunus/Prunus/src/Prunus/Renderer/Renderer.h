#pragma once
#include "Prunus/Core.h"
#include "RendererAPI.h"
#include "RenderCommand.h"

namespace Prunus
{
	class PRUNUS_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}