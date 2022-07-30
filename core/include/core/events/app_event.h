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

namespace Core
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: width(width), height(height)
		{}

		inline uint32_t GetWidth() const { return width; }
		inline uint32_t GetHeight() const { return height; }

		EVENT_CLASS_TYPE(WindowResize);

	private:
		uint32_t width;
		uint32_t height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{}

		EVENT_CLASS_TYPE(WindowClose);
	};
}