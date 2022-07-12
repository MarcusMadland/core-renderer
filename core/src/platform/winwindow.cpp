#include "platform/winwindow.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/events/appevent.h"
#include "core/events/keyevent.h"
#include "core/events/mouseevent.h"

namespace Core
{
	static bool glfwInitialized = false;

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
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window_, 
			int width_, int height_)
		{
			WindowsWindowInfo& inf = 
				*(WindowsWindowInfo*)glfwGetWindowUserPointer(window_);
			inf.width = width_;
			inf.height = height_;

			WindowResizeEvent event(width_, height_);
			inf.eventCallback(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window_)
		{
			WindowsWindowInfo& data = 
				*(WindowsWindowInfo*)glfwGetWindowUserPointer(window_);

			WindowCloseEvent event;
			data.eventCallback(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, 
			int scancode, int action, int mods)
			{
				WindowsWindowInfo& data = 
					*(WindowsWindowInfo*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(window, [](GLFWwindow* window, uint32_t keycode)
			{
				WindowsWindowInfo& data = 
					*(WindowsWindowInfo*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.eventCallback(event);
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, 
			int action, int mods)
			{
				WindowsWindowInfo& data = 
					*(WindowsWindowInfo*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(window, [](GLFWwindow* window, 
			double xOffset, double yOffset)
			{
				WindowsWindowInfo& data = 
					*(WindowsWindowInfo*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.eventCallback(event);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, 
			double xPos, double yPos)
			{
				WindowsWindowInfo& data = 
					*(WindowsWindowInfo*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
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