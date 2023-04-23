#pragma once

#include "Prunus/Core.h"
#include <string>
namespace Prunus
{
	class PRUNUS_API Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();
		void Bind();
		void Unbind();
	private:
		uint32_t m_RendererID;
	};
}