#include "platform/winwindow.h"

#include <assert.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/events/appevent.h"

namespace Core
{
	static bool glfwInitialized = false;

	Window* Window::Create(const WindowInfo& info)
	{
		return new WindowsWindow(info);
	}

	WindowsWindow::WindowsWindow(const WindowInfo& info)
	{
		winInfo.title = info.title;
		winInfo.width = info.width;
		winInfo.height = info.height;

		if (!glfwInitialized)
		{
			int success = glfwInit();
			glfwInitialized = true;
		}

		window = glfwCreateWindow((int)info.width, (int)info.height, 
			info.title, nullptr, nullptr);

		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetWindowUserPointer(window, &winInfo);
		SetVSync(true);

		// Set event callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window_, int width_, int height_)
		{
			WindowsWindowInfo& inf = *(WindowsWindowInfo*)glfwGetWindowUserPointer(window_);
			inf.width = width_;
			inf.height = height_;

			WindowResizeEvent event(width_, height_);
			inf.eventCallback(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window_)
		{
			WindowsWindowInfo& data = *(WindowsWindowInfo*)glfwGetWindowUserPointer(window_);

			WindowCloseEvent event;
			data.eventCallback(event);
		});
}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::SetVSync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		winInfo.vSync = enable;
	}

	bool WindowsWindow::GetVSync() const
	{
		return winInfo.vSync;
	}
}