#pragma once

#include "event.h"

namespace Core
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return keyCode; }

	protected:
		KeyEvent(int code)
			: keyCode(code)
		{}

	private:
		int keyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int code, int repeatCount)
			: KeyEvent(code), repeatCount(repeatCount)
		{}

		inline int GetRepeatCount() const { return repeatCount; }

		EVENT_CLASS_TYPE(KeyPressed);

	private:
		int repeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
		KeyReleasedEvent(int code)
			: KeyEvent(code)
		{}

		EVENT_CLASS_TYPE(KeyReleased);
	};
}