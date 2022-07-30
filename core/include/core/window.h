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

#include <memory>
#include <functional>

#include "core/events/event.h"

namespace Core
{
	struct WindowInfo
	{
		const char* title;
		uint32_t width;
		uint32_t height;

		WindowInfo()
			: title("window"), width(1280), height(720)
		{}
		WindowInfo(const char* name, uint32_t width, uint32_t height)
			: title(name), width(width), height(height)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetVSync(bool enable) = 0;
		virtual bool GetVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		// This is implemented in winwindow.cpp since we are creating a
		// window for Windows OS
		static Window* Create(const WindowInfo& info = WindowInfo());
	};
}