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

#include "camera.h"
#include "core/events/event.h"

namespace Core
{
	class CameraController
	{
	public:
		CameraController();

		void OnUpdate(float dt);
		void OnEvent(Core::Event& event);

		Camera& GetCamera() { return camera; }
		const Camera& GetCamera() const { return camera; }

	private:
		Camera camera;

		float deltaTime;

		bool pan = false;
		bool rotate = false;
		bool reset = false;
		float lastMouseX;
		float lastMouseY;

		// Camera Properties
		float moveSpeed = 0.1f;
		float lookSensetivity = 10.0f;
		float zoomSensetivity = 1.0f;
	};
}