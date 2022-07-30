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

#pragma once

#include <glm/glm.hpp>

#include "core/graphics/shader.h"

namespace Core
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		virtual const std::string& GetName() const override { return name; };

		void UniformMat4(const char* name, const glm::mat4& value);
		void UniformVec4(const char* name, const glm::vec4& value);

		uint32_t GetID() const { return id; }

	private:
		uint32_t Compile(uint32_t type, const std::string& source);

	private:
		uint32_t id;
		std::string name;
	};
}