#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Core
{
	class Object
	{
	public:
		virtual void Draw(uint32_t shaderID) {};

		void AddChild(Object* child);

		void SetObjectPosition(glm::vec3 newPos);
		void SetObjectRotation(glm::vec3 newRot);
		void SetObjectScale(glm::vec3 newScale);

		glm::vec3& GetObjectPosition() { return pos; };
		glm::vec3& GetObjectRotation() { return eulerRot; };
		glm::vec3& GetObjectScale() { return scale; };

		glm::mat4 GetLocalModelMatrix();

	public:
		std::vector<Object*> children = {};

	private:
		// Transform
		glm::vec3 pos =		 { 0.0f, 0.0f, 0.0f };
		glm::vec3 eulerRot = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale =	 { 1.0f, 1.0f, 1.0f };
	};
}