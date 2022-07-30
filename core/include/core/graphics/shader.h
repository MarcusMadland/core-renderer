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

#include "core.h"

#include <string>
#include <unordered_map>

namespace Core
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
		Ref<Shader> Get(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Shader>> shaders;
	};
}