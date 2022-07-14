#include "core/graphics/texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "core/debug/logger.h"

namespace Core
{
	Texture::Texture(const char* image, const char* texType, uint32_t slot)
	{
		type = texType;
		unit = slot;
		int widthImg, heightImg, numColCh;

		stbi_set_flip_vertically_on_load(true);
		stbi_ldr_to_hdr_gamma(1.0f);

		unsigned char* bytes = 
			stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

		glGenTextures(1, &id);
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
			GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 
			GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 
			GL_REPEAT);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			
		if (numColCh == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, widthImg, heightImg, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, bytes);
		}
			
		else if (numColCh == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, widthImg, heightImg, 0,
				GL_RGB, GL_UNSIGNED_BYTE, bytes);
		}
			
		else if (numColCh == 1)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, widthImg, heightImg, 0,
				GL_RED, GL_UNSIGNED_BYTE, bytes);
		}
			
		else
			Logger::LOG(Logger::LogPriority::Error, "Automatic Texture type recognition failed");

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(bytes);
	}
	void Texture::TexUnit(uint32_t shaderID, const char* uniform, uint32_t unit)
	{
		GLuint texUni = glGetUniformLocation(shaderID, uniform);
		glUseProgram(shaderID);
		glUniform1i(texUni, unit);
	}
	
	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, id);
	}
	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture::Delete()
	{
		glDeleteTextures(1, &id);
	}

}