#include "core/graphics/skybox.h"

#include <memory>

#include <glad/glad.h>
#include <stb_image.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "debug.h"

namespace Core
{
	Skybox::Skybox(uint32_t shaderID)
	{
		// Skybox
		uint32_t skyboxVbo, skyboxEbo;
		glGenVertexArrays(1, &skyboxVao);
		glGenBuffers(1, &skyboxVbo);
		glGenBuffers(1, &skyboxEbo);
		glBindVertexArray(skyboxVao);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Skybox Texture
		glGenTextures(1, &cubemapTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		// Attach textures to cubemap object
		for (unsigned int i = 0; i < 6; i++)
		{
			int width, height, nrChannels;
			unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				stbi_set_flip_vertically_on_load(false);
				if (fileFormat == "jpg")
				{
					glTexImage2D
					(
						GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						0,
						GL_RGB,
						width,
						height,
						0,
						GL_RGB,
						GL_UNSIGNED_BYTE,
						data
					);
				}
				else if (fileFormat == "png")
				{
					glTexImage2D
					(
						GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						0,
						GL_RGBA,
						width,
						height,
						0,
						GL_RGBA,
						GL_UNSIGNED_BYTE,
						data
					);
				}
				
				stbi_image_free(data);
			}
			else
			{
				Logger::LOG("Failed to load texture: ", facesCubemap[i].c_str());
				stbi_image_free(data);
			}
		}

		glUniform1i(glGetUniformLocation(shaderID, "texture_skybox"), 0);
	}
	void Skybox::Draw(uint32_t shaderID, glm::vec3 pos, glm::vec3 rot, glm::vec3 up)
	{
		glDepthFunc(GL_LEQUAL);

		glUseProgram(shaderID);

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		view = glm::mat4(glm::mat3(glm::lookAt(pos, pos + rot, up)));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

		glBindVertexArray(skyboxVao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);
	}
}