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

#include "core/graphics/opengl/ogl_buffer.h"

#include <glad/glad.h>

namespace Core
{
	static GLenum ShaderDataTypeToOpenGL(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Vec3:
			return GL_FLOAT;
		case ShaderDataType::Vec4:
			return GL_FLOAT;
		case ShaderDataType::Mat4x4:
			return GL_FLOAT;
		}

		return 0;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &id);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: count(count)
	{
		glCreateBuffers(1, &id);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &id);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &id);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(id);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& buffer)
	{
		Bind();
		buffer->Bind();
		
		const auto& elements = buffer->GetLayout().GetElements();
		for (uint32_t i = 0; i < elements.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
				i,
				elements[i].GetComponentCount(),
				ShaderDataTypeToOpenGL(elements[i].type),
				elements[i].normalized ? GL_TRUE : GL_FALSE,
				buffer->GetLayout().GetStride(),
				(const void*)(elements[i].offset)
			);
		}

		vertexBuffers.push_back(buffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& buffer)
	{
		Bind();
		buffer->Bind();

		indexBuffer = buffer;
	}
}