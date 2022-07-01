#pragma once

#include "window.h"
#include "layerstack.h"

#include "layers/imguilayer.h"

#include "events/event.h"
#include "events/keyevent.h"
#include "events/appevent.h"

namespace Core 
{
	class App
	{
	public:
		App(const char* name = "Project", 
			uint32_t width = 1280, uint32_t height = 720);
		virtual ~App() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *window; }
		inline static App& Instance() { return *instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> window;
		ImGuiLayer* imguiLayer;
		bool isRunning = true;
		LayerStack layerStack;
		float lastFrameTime = 0.0f;

		static App* instance;
	};
}