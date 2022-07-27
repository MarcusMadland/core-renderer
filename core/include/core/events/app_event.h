#pragma once

#include <memory>

namespace Core
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: width(width), height(height)
		{}

		inline uint32_t GetWidth() const { return width; }
		inline uint32_t GetHeight() const { return height; }

		EVENT_CLASS_TYPE(WindowResize);

	private:
		uint32_t width;
		uint32_t height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{}

		EVENT_CLASS_TYPE(WindowClose);
	};
}