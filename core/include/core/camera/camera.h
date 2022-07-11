#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "core/events/event.h"

struct GLFWwindow;

namespace Core
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Update(float dt, uint32_t shaderID);
		void OnEvent(Core::Event& event);

		void SetNearAndFar(float nearPlane, float farPlane);
		void SetCameraSize(uint32_t width, uint32_t height);
		void SetPosition(glm::vec3 pos);
		void SetRotation(glm::vec3 rot);

		glm::vec3 GetPosition() { return position; }
		glm::vec3 GetRotation() { return rotation; }

	private:
		void UpdateInput();

	private:
		GLFWwindow* winwindow;
		float deltaTime = 0.0f;

		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 matrix = glm::mat4(1.0f);

		bool pan = false;
		bool rotate = false;
		bool reset = false;

		// Camera properties
		uint32_t width = 1280;
		uint32_t height = 720;
		float fov = 45.0f;
		float nearPlane = 0.1f;
		float farPlane = 5500.0f;
		float speed = 0.2f;
		float sensetivity = 10.0f;

		// Input
		double mouseX = 0.0f;
		double lastMouseX = 0.0f;
		double mouseY = 0.0f;
		double lastMouseY = 0.0f;
	};
}