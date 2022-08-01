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

#include "core/graphics/buffer.h"

#include "core.h"
#include "core/graphics/renderer.h"

#include "core/graphics/opengl/ogl_buffer.h"

namespace Core
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case RendererAPI::GraphicsAPI::None: 
			return nullptr;

		case RendererAPI::GraphicsAPI::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case RendererAPI::GraphicsAPI::None:
			return nullptr;

		case RendererAPI::GraphicsAPI::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		return nullptr;
	}

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case RendererAPI::GraphicsAPI::None:
			return nullptr;

		case RendererAPI::GraphicsAPI::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		return nullptr;
	}

}