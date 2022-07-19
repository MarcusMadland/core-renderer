#include "core/object/light.h"

#include <iostream>
#include <math.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "core/graphics/shader.h"

namespace Core
{
	Light::Light(Camera* camera, LightType lightType)
		: lightType(lightType), camera(camera)
	{
		SetLightType(lightType);
		Init();
	}

	void Light::Init()
	{
		SetObjectScale(0.1f, 0.1f, 0.1f);
		SetObjectPosition(0.0f, 2.0f, 0.0f);

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;
		std::vector<uint32_t> indices;
		std::vector<Vertex> vertices;

		for (glm::vec3 i : lightVertices)
			positions.push_back(i);

		for (glm::vec3 i : lightNormals)
			normals.push_back(i);

		for (glm::vec2 i : lightTexCoords)
			texCoords.push_back(i);

		for (uint32_t i : lightIndices)
			indices.push_back(i);

		for (uint32_t i = 0; i < positions.size(); i++)
			vertices.push_back(Vertex(positions[i], normals[i], texCoords[i]));

		mesh = new StaticMeshObject({ StaticMesh(vertices, indices, { Texture() }) });
		mesh->SetObjectScale(0.1f, 0.1f, 0.1f);
	}

	glm::vec3 Light::RotMatToEulerRot(glm::mat4& R)
	{
		{
			float sy = sqrt(R[0][0] * R[0][0] + R[1][0] * R[1][0]);

			bool singular = sy < 1e-6;

			float x, y, z;
			if (!singular)
			{
				x = atan2(R[2][1], R[2][2]);
				y = atan2(-R[2][0], sy);
				z = atan2(R[1][0], R[0][0]);
			}
			else
			{
				x = atan2(-R[1][2], R[1][1]);
				y = atan2(-R[2][0], sy);
				z = 0;
			}
			return glm::vec3(x, y, z);

		}
	}

	void Light::Draw(uint32_t shaderID)
	{
		if (!mesh)
			return;

		// Update shader with model matrix (transform)
		glUniformMatrix4fv(glGetUniformLocation(shaderID, "uObject"),
			1, false, glm::value_ptr(GetLocalModelMatrix()));

		// Update
		glUniform1ui(glGetUniformLocation(shaderID, "light_type"),
			(uint32_t)lightType);

		// Update shader with light color
		glUniform4f(glGetUniformLocation(shaderID, "light_color"),
			lightColor.r, lightColor.g, lightColor.b, lightColor.a);

		// Update shader with light position
		glUniform3f(glGetUniformLocation(shaderID, "light_pos"),
			GetObjectPosition().x, GetObjectPosition().y, GetObjectPosition().z);

		glm::vec3 desiredRot = RotMatToEulerRot(camera->GetRotationMatrix()) * (float)(180.0 / 3.1415);

		mesh->SetObjectPosition(GetObjectPosition());
		mesh->Draw(shaderID);
	}
	void Light::SetLightColor(glm::vec4 lightColor)
	{
		Light::lightColor = lightColor;
	}
	void Light::SetLightColor(float r, float g, float b, float a)
	{
		lightColor = { r,g,b,a };
	}

	void Light::SetLightType(LightType lightType)
	{
		Light::lightType = lightType;
	}
	
}