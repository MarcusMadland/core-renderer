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