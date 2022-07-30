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

#include "core/graphics/shader.h"

#include "core/graphics/renderer.h"

#include "core/graphics/opengl/ogl_shader.h"

namespace Core
{
	Ref<Shader> Shader::Create(const std::string& vertexShaderPath,
		const std::string& fragmentShaderPath)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case RendererAPI::GraphicsAPI::None:
			return nullptr;

		case RendererAPI::GraphicsAPI::OpenGL:
			return std::make_shared<OpenGLShader>(vertexShaderPath, fragmentShaderPath);
		}

		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		shaders[shader->GetName()] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& vertexShaderPath, 
		const std::string& fragmentShaderPath)
	{
		auto shader = Shader::Create(vertexShaderPath, fragmentShaderPath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		return shaders[name];
	}

}