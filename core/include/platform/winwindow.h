#pragma once

#include "core/window.h"

#include <GLFW/glfw3.h>

namespace Core
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowInfo& info);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline void SetEventCallback(const EventCallbackFn& callback) override \
			{ winInfo.eventCallback = callback; }

		inline uint32_t GetWidth() const override { return winInfo.width; }
		inline uint32_t GetHeight() const override { return winInfo.height; }
		inline virtual void* GetNativeWindow() const { return window; }

		void SetVSync(bool enable) override;
		bool GetVSync() const override;

	private:
		struct WindowsWindowInfo
		{
			const char* title;
			uint32_t width;
			uint32_t height;
			bool vSync;

			EventCallbackFn eventCallback;
		};

		GLFWwindow* window;
		WindowsWindowInfo winInfo;
	};
}