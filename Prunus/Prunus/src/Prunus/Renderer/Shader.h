#pragma once

#include "Prunus/Core.h"
#include <string>
#include <glm/glm.hpp>
namespace Prunus
{
	class PRUNUS_API Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		static Shader* Create(const std::string & vertexSrc, const std::string & fragmentSrc);
	private:
		uint32_t m_RendererID;
	};
}