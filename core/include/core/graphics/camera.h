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

#include <glm/glm.hpp>

namespace Core
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const float fov, const float width, const float height, 
			const float near, const float far);
		virtual ~Camera() = default;

		void RecalculateViewMatrix();

		const glm::vec3& GetPosition() const { return pos; }
		void SetPosition(const glm::vec3& position);

		const glm::vec3& GetRotation() const { return eulerRot; }
		void SetRotation(const glm::vec3& rotation);

		const glm::vec3& GetForwardVector() const { return forwardVector; }
		void SetForwardVector(const glm::vec3& forwardVec);

		const glm::vec3& GetUpVector() const { return upVector; }
		void SetUpVector(const glm::vec3& upVec);

		const glm::mat4& GetProjectionMatrix() const { return proj; }
		const glm::mat4& GetViewMatrix() const { return view; }
		const glm::mat4& GetViewProjectionMatrix() const { return viewProj; }

	private:
		glm::mat4 view;
		glm::mat4 proj;
		glm::mat4 viewProj;

		glm::vec3 forwardVector;
		glm::vec3 upVector;

		glm::vec3 pos;
		glm::vec3 eulerRot;
	};
}