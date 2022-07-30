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

#include "core/app.h"

#include <windows.h>

#include <GLFW/glfw3.h>

#include "core/graphics/renderer.h"

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

		Renderer::Init();

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
			float time = (float)glfwGetTime(); // @TODO Should be support diff platform
			deltaTime = time - lastFrameTime;
			lastFrameTime = time;

			for (Layer* layer : layerStack)
				layer->OnUpdate(deltaTime);

			imguiLayer->Begin();

			for (Layer* layer : layerStack)
				layer->OnImGuiRender();

			imguiLayer->End();

			window->OnUpdate();
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
}