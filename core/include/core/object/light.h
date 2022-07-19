#pragma once

#include <memory>

#include "object.h"
#include "staticmesh.h"
#include "core/camera/camera.h"

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
		Light(Camera* camera, LightType lightType = LightType::Point);

		virtual void Draw(uint32_t shaderID) override;

		void SetLightColor(glm::vec4 lightColor);
		void SetLightColor(float r, float g, float b, float a);
		void SetLightType(LightType lightType);

	private:
		void Init();
		glm::vec3 RotMatToEulerRot(glm::mat4& R);
		
		
	private:
		StaticMeshObject* mesh;
		Camera* camera;

		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		LightType lightType = LightType::Point;

		// MESH DATA
		glm::vec3 lightVertices[6] =
		{
			glm::vec3(-0.5f, -0.5f, 0.0f),
			glm::vec3(-0.5f,  0.5f, 0.0f),
			glm::vec3( 0.5f,  0.5f, 0.0f),
			glm::vec3( 0.5f, -0.5f, 0.0f),
		};
		glm::vec2 lightTexCoords[6] =
		{
			glm::vec2(0, 0),
			glm::vec2(0, 1),
			glm::vec2(1, 1),
			glm::vec2(1, 0),
		};
		glm::vec3 lightNormals[6] =
		{
			
		};
		uint32_t lightIndices[6] =
		{
			0, 2, 1, 
			0, 3, 2,
		};
	};
}