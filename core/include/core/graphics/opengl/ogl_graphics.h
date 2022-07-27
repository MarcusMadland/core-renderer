#pragma once

#include "core/graphics/graphics.h"

#include <GLFW/glfw3.h>

namespace Core
{
	class OpenGLGraphics : public Graphics
	{
	public:
		OpenGLGraphics(GLFWwindow* windowHandle);
		
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* windowHandle;
	};
}
