#pragma once

#include "window.h"
#include "layerstack.h"

#include "debug/instrumentor.h"
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

		inline static App& Instance() { return *instance; }
		inline Window& GetWindow() { return *window; }

		// Performance
		void AddVertCount(uint32_t verts);
		void AddDrawCalls(uint32_t calls);
		void ResetVertCount();
		void ResetDrawCalls();

		inline uint32_t& GetVertCount() { return vertCount; }
		inline uint32_t& GetDrawCalls() { return drawCalls; }
		inline float& GetDeltaTime() { return deltaTime; }
		inline std::vector<TimerResult>& GetTimerResults() { return timerResults; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> window;
		ImGuiLayer* imguiLayer;
		bool isRunning = true;
		LayerStack layerStack;
		std::vector<TimerResult> timerResults;

		float lastFrameTime = 0.0f;
		float deltaTime = 0.0f;

		uint32_t vertCount = 0;
		uint32_t drawCalls = 0;

		static App* instance;
	};
}