#pragma once

#include <memory>

#include "object.h"
#include "staticmesh.h"

namespace Core
{
	class Light : public Object
	{
	public:
		Light();

		virtual void Draw(uint32_t shaderID) override;

	private:
		glm::vec3 lightVertices[36] =
		{
			glm::vec3(-1, -1, -1),
			glm::vec3(1, -1, -1),
			glm::vec3(1, 1, -1),
			glm::vec3(-1, 1, -1),
			glm::vec3(-1, -1, 1),
			glm::vec3(1, -1, 1),
			glm::vec3(1, 1, 1),
			glm::vec3(-1, 1, 1)
		};

		glm::vec2 lightTexCoords[36] =
		{
			glm::vec2(0, 0),
			glm::vec2(1, 0),
			glm::vec2(1, 1),
			glm::vec2(0, 1)
		};

		glm::vec3 lightNormals[36] =
		{
			glm::vec3(0, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 0, -1),
			glm::vec3(-1, 0, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, -1, 0)
		};

		uint32_t lightIndices[36] =
		{
			0, 1, 3, 3, 1, 2,
			1, 5, 2, 2, 5, 6,
			5, 4, 6, 6, 4, 7,
			4, 0, 7, 7, 0, 3,
			3, 2, 7, 7, 2, 6,
			4, 5, 0, 0, 5, 1
		};

		StaticMesh* mesh;
	};
}