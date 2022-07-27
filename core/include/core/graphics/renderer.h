#pragma once

#include "renderer_command.h"

#include "camera.h"
#include "shader.h"

namespace Core
{
	class Renderer
	{
	public:
		static void BeginScene(Camera& camera); 
		static void EndScene();   
		
		static void Submit(const std::shared_ptr<VertexArray>& vao,
			const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::GraphicsAPI GetGraphicsAPI() { return RendererAPI::GetAPI(); }
	
	private:
		struct SceneData
		{
			glm::mat4 viewProj;
		};

		static SceneData* sceneData;
	};
}