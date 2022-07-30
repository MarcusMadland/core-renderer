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

#include "core/window.h"

#include "core/graphics/opengl/ogl_graphics.h"

struct GLFWwindow;

namespace Core
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowInfo& info);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline void SetEventCallback(const EventCallbackFn& callback) override \
			{ winInfo.eventCallback = callback; }

		inline uint32_t GetWidth() const override { return winInfo.width; }
		inline uint32_t GetHeight() const override { return winInfo.height; }
		inline virtual void* GetNativeWindow() const { return window; }

		void SetVSync(bool enable) override;
		bool GetVSync() const override;

	private:
		struct WindowsWindowInfo
		{
			WindowsWindowInfo()
				: title("winwindow")
				, width(1280)
				, height(720)
				, vSync(true)
			{}

			const char* title;
			uint32_t width;
			uint32_t height;
			bool vSync;

			EventCallbackFn eventCallback;
		};

		GLFWwindow* window;
		Graphics* graphics;
		WindowsWindowInfo winInfo;
	};
}