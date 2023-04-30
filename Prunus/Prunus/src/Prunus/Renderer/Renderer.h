#pragma once
#include "Prunus/Core.h"

namespace Prunus
{
	enum class RendererAPI
	{
		None = 0,

		OpenGL = 1
	};

	class PRUNUS_API Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}