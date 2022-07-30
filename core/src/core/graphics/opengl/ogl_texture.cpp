/*
 * Copyright 2022 Marcus Madland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissionsand
 * limitations under the License.
 */

#include "core/graphics/opengl/ogl_texture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Core
{
	OpenGLTexture2D::OpenGLTexture2D(const char* path)
	{
		stbi_set_flip_vertically_on_load(true);

		int w, h, ch;
		unsigned char* bytes = stbi_load(path, &w, &h, &ch, 0);

		width = (uint32_t)w;
		height = (uint32_t)h;

		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, 
			ch == 4 ? GL_RGBA8 : GL_RGB8, width, height);

		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(id, 0, 0, 0, width, height, 
			ch == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, bytes);

		stbi_image_free(bytes);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &id);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, id);
	}
}