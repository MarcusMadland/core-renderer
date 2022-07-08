#include "core/camera/camera.h"

#include <iostream>

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "core/app.h"
#include "core/events/mouseevent.h"
#include "core/events/keyevent.h"
#include "core/debug/logger/logger.h"

namespace Core
{
	Camera::Camera()
	{
		winwindow = (GLFWwindow*)
			(App::Instance().GetWindow().GetNativeWindow());
	}
	Camera::~Camera()
	{
	}

	void Camera::Update(uint32_t shaderID)
	{
		UpdateInput();

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		proj = glm::perspective(glm::radians(fov), (float)(width / height),
			nearPlane, farPlane);
		view = glm::lookAt(position, (position + rotation), upVector);
		
		matrix = proj * view;

		glUniformMatrix4fv(glGetUniformLocation(shaderID, "uCamera"),
			1, GL_FALSE, glm::value_ptr(matrix));
	}
	void Camera::OnEvent(Core::Event& event)
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
				if (reset)
					mouseX = e.GetX(); mouseY = e.GetY();

				mouseX = (mouseX - lastMouseX);
				mouseY = (mouseY - lastMouseY);

				lastMouseX = e.GetX();
				lastMouseY = e.GetY();

				if (pan)
				{
					if (reset)
					{
						position += speed * (float)mouseX *
							-glm::normalize(glm::cross(rotation, upVector));

						position += speed * (float)mouseY * upVector;
					}
					reset = true;
				}
					
				else if (rotate)
				{
					if (reset)
					{
						glm::vec3 newOrientation = glm::rotate(rotation,
							glm::radians((float)-mouseY * sensetivity),
							glm::normalize(glm::cross(rotation, upVector)));

						if (abs(glm::angle(newOrientation, upVector) - glm::radians(90.0f))
							<= glm::radians(85.0f))
						{
							rotation = newOrientation;
						}
						rotation = glm::rotate(rotation,
							glm::radians((float)-mouseX * sensetivity), upVector);
					}
					reset = true;
				}
				return false;
			});

		dispatcher.Dispatch<MouseScrolledEvent>(
			[&](MouseScrolledEvent& e)
			{
				position += e.GetYOffset() * 0.1f * rotation;

				return false;
			});

		dispatcher.Dispatch<WindowResizeEvent>(
			[&](WindowResizeEvent& e)
			{
				width = e.GetWidth();
				height = e.GetHeight();

				return false;
			});
	}

	void Camera::SetNearAndFar(float nearPlane, float farPlane)
	{
		Camera::nearPlane = nearPlane;
		Camera::farPlane = farPlane;
	}
	void Camera::SetCameraSize(uint32_t width, uint32_t height)
	{
		Camera::width = width;
		Camera::height = height;
	}
	void Camera::SetPosition(glm::vec3 pos)
	{
		position = pos;
	}
	void Camera::SetRotation(glm::vec3 rot)
	{
		rotation = rot;
	}
	void Camera::UpdateInput()
	{
		if (pan || rotate)
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		else
			ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
	}
}