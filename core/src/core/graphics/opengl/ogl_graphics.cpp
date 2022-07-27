#include "core/graphics/opengl/ogl_graphics.h"

#include <iostream>

namespace Core
{
	OpenGLGraphics::OpenGLGraphics(GLFWwindow* windowHandle)
		: windowHandle(windowHandle)
	{
	}

	void OpenGLGraphics::Init()
	{
		glfwMakeContextCurrent(windowHandle);
	}
	
	void OpenGLGraphics::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}
}
