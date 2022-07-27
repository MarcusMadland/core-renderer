#pragma once

#include "renderer_api.h"

namespace Core
{
	class RendererCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			rendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			rendererAPI->Clear();
		}
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vao)
		{
			rendererAPI->DrawIndexed(vao);
		}

	private:
		static RendererAPI* rendererAPI;
	};
}