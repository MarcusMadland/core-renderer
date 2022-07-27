#include "core/graphics/buffer.h"

#include "core/graphics/renderer.h"

#include "core/graphics/opengl/ogl_buffer.h"

namespace Core
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case RendererAPI::GraphicsAPI::None: 
			return nullptr;

		case RendererAPI::GraphicsAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case RendererAPI::GraphicsAPI::None:
			return nullptr;

		case RendererAPI::GraphicsAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		return nullptr;
	}

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case RendererAPI::GraphicsAPI::None:
			return nullptr;

		case RendererAPI::GraphicsAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		return nullptr;
	}

}