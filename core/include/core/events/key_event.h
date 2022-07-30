/*
 * Copyright 2022 Marcus Madland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissionsand
 * limitations under the License.
 */

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
	public:
		KeyReleasedEvent(int code)
			: KeyEvent(code)
		{}

		EVENT_CLASS_TYPE(KeyReleased);
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}