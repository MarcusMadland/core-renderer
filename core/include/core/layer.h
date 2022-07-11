#pragma once

#include "events/event.h"

namespace Core 
{
	class Layer
	{
	public:
		Layer(const char* name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(const float& dt) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const char* GetName() const { return layerName; }

	protected:
		const char* layerName;
	};
}