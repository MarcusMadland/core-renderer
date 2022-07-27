#pragma once

#include "core/window.h"

#include "core/graphics/opengl/ogl_graphics.h"

struct GLFWwindow;

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
			WindowsWindowInfo()
				: title("winwindow")
				, width(1280)
				, height(720)
				, vSync(true)
			{}

			const char* title;
			uint32_t width;
			uint32_t height;
			bool vSync;

			EventCallbackFn eventCallback;
		};

		GLFWwindow* window;
		Graphics* graphics;
		WindowsWindowInfo winInfo;
	};
}