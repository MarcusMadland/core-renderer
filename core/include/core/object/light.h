#pragma once

#include <memory>

#include "object.h"
#include "staticmesh.h"

namespace Core
{
	class Light : public Object
	{
	public:
		enum class LightType
		{
			Point,
			Directional,
			Spot
		};

	public:
		Light(LightType lightType = LightType::Point);

		virtual void Draw(uint32_t shaderID) override;

		void SetLightColor(glm::vec4 lightColor);
		void SetLightColor(float r, float g, float b, float a);
		void SetLightType(LightType lightType);

	private:
		void Init();

	private:
		StaticMesh* mesh;
		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		LightType lightType = LightType::Point;

		// MESH DATA
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
	};
}