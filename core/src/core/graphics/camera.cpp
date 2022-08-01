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
		, forwardVector({0.0f, 0.0f, -1.0f})
		, upVector({ 0.0f, 1.0f, 0.0f })
	{
		proj = glm::perspective(glm::radians(fov), (width / height), near, far);
		view = glm::lookAt(GetPosition(), (GetPosition() + forwardVector), upVector);

		viewProj = proj * view;
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		pos = position;
	}

	void Camera::SetRotation(const glm::vec3& rotation)
	{
		eulerRot = rotation;
	}

	void Camera::SetForwardVector(const glm::vec3& forwardVec)
	{
		forwardVector = forwardVec;
	}

	void Camera::SetUpVector(const glm::vec3& upVec)
	{
		upVector = upVec;
	}

	void Camera::RecalculateViewMatrix()
	{
		view = glm::lookAt(GetPosition(), (GetPosition() + forwardVector), upVector);

		viewProj = proj * view;
	}
}