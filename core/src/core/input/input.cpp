#include "core/input/input.h"

#include <GLFW/glfw3.h>

#include "core/app.h"

namespace Core 
{
	inline bool Input::IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>
			(App::Instance().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	inline bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>
			(App::Instance().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	inline std::pair<double, double> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>
			(App::Instance().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { xpos, ypos };
	}

	inline double Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	inline double Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}

}