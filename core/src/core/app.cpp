#include "core/app.h"

#include <windows.h>

#include <GLFW/glfw3.h>

#include "debug.h"

namespace Core
{
	#define BIND_EVENT_FN(x) std::bind(&App::x, \
		this, std::placeholders::_1)
	App* App::instance = nullptr;

	App::App(const char* name, uint32_t width, uint32_t height)
	{
		if (!instance)
		{
			// Initialize core
			
		}

		instance = this;

		window = std::unique_ptr<Window>(Window::Create({ name, 
			width, height }));
		window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		imguiLayer = new ImGuiLayer();
		PushOverlay(imguiLayer);
	}

	void App::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void App::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
	}

	void App::Run()
	{
		while (isRunning)
		{
			PROFILE_SCOPE("App");

			float time = (float)glfwGetTime(); // @TODO Should be support diff platform
			deltaTime = time - lastFrameTime;
			lastFrameTime = time;

			{
				PROFILE_SCOPE("LayerStack");
				for (Layer* layer : layerStack)
					layer->OnUpdate(deltaTime);
			}

			{
				PROFILE_SCOPE("ImGui");
				imguiLayer->Begin();

				for (Layer* layer : layerStack)
					layer->OnImGuiRender();

				imguiLayer->End();
			}
			
			{
				PROFILE_SCOPE("Window");
				window->OnUpdate();
			}
			
		}
	}
	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		return true;
	}

	void App::AddVertCount(uint32_t verts)
	{
		vertCount = vertCount + verts;
	}
	void App::AddDrawCalls(uint32_t calls)
	{
		drawCalls = drawCalls + calls;
	}
	void App::ResetVertCount()
	{
		vertCount = 0;
	}
	void App::ResetDrawCalls()
	{
		drawCalls = 0;
	}
}