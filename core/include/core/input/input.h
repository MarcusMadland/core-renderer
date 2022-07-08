#pragma once

#include <vector>

namespace Core
{
	class Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(int keycode);
		inline static bool IsMouseButtonPressed(int button);

		inline static std::pair<double, double> GetMousePosition();
		inline static double GetMouseX();
		inline static double GetMouseY();
	};
}