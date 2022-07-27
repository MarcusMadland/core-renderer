#pragma once

#include "window.h"
#include "layer/layer_stack.h"

#include "layer/layers/imgui_layer.h"

#include "events/event.h"
#include "events/key_event.h"
#include "events/app_event.h"

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

		inline static App& Instance() { return *instance; }
		inline Window& GetWindow() { return *window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> window;
		ImGuiLayer* imguiLayer;
		bool isRunning = true;
		LayerStack layerStack;

		float lastFrameTime = 0.0f;
		float deltaTime = 0.0f;

		static App* instance;
	};
}