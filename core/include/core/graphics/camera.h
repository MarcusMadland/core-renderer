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


		const glm::vec3& GetPosition() const { return pos; }
		void SetPosition(const glm::vec3& position);

		const glm::vec3& GetRotation() const { return eulerRot; }
		void SetRotation(const glm::vec3& rotation);

		const glm::mat4& GetProjectionMatrix() const { return proj; }
		const glm::mat4& GetViewMatrix() const { return view; }
		const glm::mat4& GetViewProjectionMatrix() const { return viewProj; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 view;
		glm::mat4 proj;
		glm::mat4 viewProj;

		glm::vec3 pos;
		glm::vec3 eulerRot;
	};
}