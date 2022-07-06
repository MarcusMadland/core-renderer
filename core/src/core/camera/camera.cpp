#include "core/camera/camera.h"

#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace Core
{
	Camera::Camera()
	{
	}
	Camera::~Camera()
	{
	}

	void Camera::Update(uint32_t shaderID)
	{
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		view = glm::lookAt(position, (position + rotation), upVector);
		proj = glm::perspective(glm::radians(fov), (float)(width / height),
			nearPlane, farPlane);
		
		matrix = view * proj;

		glUniformMatrix4fv(glGetUniformLocation(shaderID, "uCamera"),
			1, GL_FALSE, glm::value_ptr(matrix));
	}
	void Camera::OnEvent(Core::Event& event)
	{
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
}