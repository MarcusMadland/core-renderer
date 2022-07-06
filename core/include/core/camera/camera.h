#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "core/events/event.h"

namespace Core
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Update(uint32_t shaderID);
		void OnEvent(Core::Event& event);

		void SetNearAndFar(float nearPlane, float farPlane);
		void SetCameraSize(uint32_t width, uint32_t height);
		void SetPosition(glm::vec3 pos);
		void SetRotation(glm::vec3 rot);

	private:
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 matrix = glm::mat4(1.0f);

		uint32_t width = 1280;
		uint32_t height = 720;
		float fov = 90.0f;
		float nearPlane = 0.1f;
		float farPlane = 5500.0f;
	};
}