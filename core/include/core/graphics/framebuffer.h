#pragma once

#include <memory>

namespace Core
{
	class Framebuffer
	{
	public:
		Framebuffer() = default;
		Framebuffer(uint32_t shaderID);

		void Bind();
		void Unbind();

		const inline uint32_t GetTexture() { return texture; }

	private:
		uint32_t rectVao = 0;
		uint32_t fbo = 0;
		uint32_t rbo = 0;
		uint32_t texture = 0;
		uint32_t shaderID = 0;

		uint32_t width = 1280;
		uint32_t height = 720;

	private:
		float rectangleData[24] =
		{
			 1.0f, -1.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f, 0.0f,
			-1.0f,  1.0f, 0.0f, 1.0f,

			 1.0f,  1.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f, 1.0f,
		};
	};
}