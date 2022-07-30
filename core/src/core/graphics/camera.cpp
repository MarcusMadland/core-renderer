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

#include "core/graphics/camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Core
{
	Camera::Camera(const float fov, const float width, const float height, 
		const float near, const float far)
		: view(1.0f)
		, eulerRot({0.0f, 0.0f, 0.0f})
		, pos({0.0f, 0.0f, 0.0f})
	{
		proj = glm::perspective(fov, (width / height), near, far);
		viewProj = proj * view;
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		pos = position;
		RecalculateViewMatrix();
	}

	void Camera::SetRotation(const glm::vec3& rotation)
	{
		eulerRot = rotation;
		RecalculateViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
			glm::radians(eulerRot.x),
			glm::vec3(1.0f, 0.0f, 0.0f));

		const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
			glm::radians(eulerRot.y),
			glm::vec3(0.0f, 1.0f, 0.0f));

		const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
			glm::radians(eulerRot.z),
			glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 roationMatrix = transformY * transformX * transformZ;
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), pos);
		
		glm::mat4 transform = translationMatrix * roationMatrix;

		view = glm::inverse(transform);
		viewProj = proj * view;
	}
}