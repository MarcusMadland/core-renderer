#pragma once

#include <utility>

namespace Core
{
	class Input
	{
	public:
		Input() = default;
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* instance;
	};
}