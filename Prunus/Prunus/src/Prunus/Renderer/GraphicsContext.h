#pragma once
#include "Prunus/Core.h"

namespace Prunus
{
	class PRUNUS_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}