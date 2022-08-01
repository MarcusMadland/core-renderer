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

#include "core/graphics/renderer.h"

#include "core/graphics/opengl/ogl_shader.h" // TODO@ Should not need to cast

namespace Core
{
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RendererCommand::Init();
	}

	void Renderer::BeginScene(Camera& camera)
	{
		sceneData->viewProj = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
		// @TODO 
	}

	void Renderer::Submit(const Ref<VertexArray>& vao, const Ref<Shader>& shader, 
		const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UniformMat4("u_Camera", sceneData->viewProj);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UniformMat4("u_Model", transform);

		vao->Bind();
		RendererCommand::DrawIndexed(vao);
	}

}