#include "core/graphics/renderer.h"

namespace Core
{
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
		sceneData->viewProj = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
		// @TODO 
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vao,
		const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UniformMat4("u_Camera", sceneData->viewProj);
		shader->UniformMat4("u_Model", transform);

		vao->Bind();
		RendererCommand::DrawIndexed(vao);
	}

}