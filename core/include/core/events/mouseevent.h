#pragma once

#include "core/events/event.h"

namespace Core
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: mouseX(x), mouseY(y) {}

		inline float GetX() const { return mouseX; }
		inline float GetY() const { return mouseY; }

		EVENT_CLASS_TYPE(MouseMoved)
	private:
		float mouseX, mouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: offsetX(xOffset), offsetY(yOffset) {}

		inline float GetXOffset() const { return offsetX; }
		inline float GetYOffset() const { return offsetY; }

		EVENT_CLASS_TYPE(MouseScrolled)
	private:
		float offsetX, offsetY;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return button; }

	protected:
		MouseButtonEvent(int button)
			: button(button) {}

		int button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}