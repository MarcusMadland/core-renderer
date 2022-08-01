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

#include "core/graphics/camera_controller.h"

#include <imgui.h>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/events/mouse_event.h"
#include "core/events/app_event.h"

namespace Core
{
	CameraController::CameraController()
	{
		camera = Camera(90.0f, 1280.0f, 720.0f, 0.1, 500.0f);
	}

	void CameraController::OnUpdate(float dt)
	{
		deltaTime = dt;

		if (pan || rotate)
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		else
			ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);

		camera.RecalculateViewMatrix();
	}

	void CameraController::OnEvent(Core::Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseButtonPressedEvent>(
			[&](MouseButtonPressedEvent& e)
			{
				if (e.GetMouseButton() == 0)
					rotate = true;
				if (e.GetMouseButton() == 1)
					pan = true;
				if (e.GetMouseButton() == 2)
					pan = true;

				return false;
			});

		dispatcher.Dispatch<MouseButtonReleasedEvent>(
			[&](MouseButtonReleasedEvent& e)
			{
				if (e.GetMouseButton() == 0)
					rotate = false;
				if (e.GetMouseButton() == 1)
					pan = false;
				if (e.GetMouseButton() == 2)
					pan = false;

				reset = false;

				return false;
			});

		dispatcher.Dispatch<MouseMovedEvent>(
			[&](MouseMovedEvent& e)
			{
				static float mouseX = 0;
				static float mouseY = 0;

				if (reset)
				{
					mouseX = e.GetX();
					mouseY = e.GetY();
				}

				mouseX = (mouseX - lastMouseX);
				mouseY = (mouseY - lastMouseY);

				lastMouseX = e.GetX();
				lastMouseY = e.GetY();

				if (pan)
				{
					if (reset)
					{
						camera.SetPosition(camera.GetPosition() + deltaTime * (moveSpeed * mouseX) *
							-glm::normalize(glm::cross(camera.GetForwardVector(), camera.GetUpVector())));

						camera.SetPosition((camera.GetPosition() + deltaTime * (moveSpeed * mouseY) * 
							camera.GetUpVector()));
					}
					reset = true;
				}

				else if (rotate)
				{
					if (reset)
					{
						glm::vec3 newForwardVector = glm::rotate(camera.GetForwardVector(),
							glm::radians(deltaTime * -mouseY * lookSensetivity),
							glm::normalize(glm::cross(camera.GetForwardVector(), camera.GetUpVector())));

						if (abs(glm::angle(newForwardVector, camera.GetUpVector()) - glm::radians(90.0f))
							<= glm::radians(85.0f))
						{
							camera.SetForwardVector(newForwardVector);
						}
						camera.SetForwardVector(glm::rotate(camera.GetForwardVector(),
							glm::radians(deltaTime * -mouseX * lookSensetivity),
							camera.GetUpVector()));
					}
					reset = true;
				}
				return false;
			});

		dispatcher.Dispatch<MouseScrolledEvent>(
			[&](MouseScrolledEvent& e)
			{
				camera.SetPosition(camera.GetPosition() +
					(deltaTime * zoomSensetivity * e.GetYOffset()) * camera.GetForwardVector());

				return false;
			});

		dispatcher.Dispatch<WindowResizeEvent>(
			[&](WindowResizeEvent& e)
			{
				return false;
			});
	}

}