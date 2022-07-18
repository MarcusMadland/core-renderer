#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Core
{
	class Skybox
	{
	public:
		Skybox() = default;
		Skybox(uint32_t shaderID);

		void Draw(uint32_t shaderID, glm::vec3 pos, glm::vec3 rot, glm::vec3 up);

	private:
		std::string cubemapFolderName = "example";
		std::string fileFormat = "jpg";

		uint32_t width = 1280;
		uint32_t height = 720;

		uint32_t skyboxVao = 0;
		uint32_t cubemapTexture = 0;

		float skyboxVertices[24] =
		{
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f
		};

		unsigned int skyboxIndices[36] =
		{
			1, 2, 6,
			6, 5, 1,

			0, 4, 7,
			7, 3, 0,

			4, 5, 6,
			6, 7, 4,

			0, 3, 2,
			2, 1, 0,

			0, 1, 5,
			5, 4, 0,

			3, 7, 6,
			6, 2, 3
		};

		std::string facesCubemap[6] =
		{
			"../core/assets/cubemaps/" + cubemapFolderName + "/right." + fileFormat,
			"../core/assets/cubemaps/" + cubemapFolderName + "/left." + fileFormat,
			"../core/assets/cubemaps/" + cubemapFolderName + "/top." + fileFormat,
			"../core/assets/cubemaps/" + cubemapFolderName + "/bottom." + fileFormat,
			"../core/assets/cubemaps/" + cubemapFolderName + "/front." + fileFormat,
			"../core/assets/cubemaps/" + cubemapFolderName + "/back." + fileFormat,
		};
	};
}