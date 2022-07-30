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

#include <string>
#include <functional>

namespace Core
{
	enum class EventType
	{
		None = 0,

		WindowClose, 
		WindowResize, 

		KeyPressed,
		KeyReleased,
		KeyTyped,

		MouseMoved,
		MouseScrolled,
		MouseButtonPressed,
		MouseButtonReleased,
	};
	
	#define EVENT_CLASS_TYPE(type) \
		static EventType GetStaticType() { return EventType::##type; }\
		virtual EventType GetEventType() const override { return GetStaticType(); }\

	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;

		bool handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: event(event)
		{}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				event.handled = func(*(T*)&event);
				return true;
			}
			return false;
		}

	private:
		Event& event;
	};
}