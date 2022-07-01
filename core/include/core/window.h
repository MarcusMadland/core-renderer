#pragma once

#include <memory>
#include <functional>

#include "core/events/event.h"

namespace Core
{
	struct WindowInfo
	{
		const char* title;
		uint32_t width;
		uint32_t height;

		WindowInfo()
			: title("core-renderer"), width(1280), height(720)
		{}
		WindowInfo(const char* name, uint32_t width, uint32_t height)
			: title(name), width(width), height(height)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetVSync(bool enable) = 0;
		virtual bool GetVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		// This is implemented in winwindow.h since we are creating a
		// window for Windows OS
		static Window* Create(const WindowInfo& info = WindowInfo());
	};
}