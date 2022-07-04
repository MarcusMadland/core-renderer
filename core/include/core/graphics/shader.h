#pragma once

#include "core.h"

#include <memory>
#include <string>

namespace Core
{
	class Shader
	{
	public:
		Shader() = default;
		~Shader();

		static Shader* FromGLSL(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
		void Use();
		
		uint32_t GetID() { return id; }

		// Shader uniforms
		void SetFloat(const std::string& name, float value,
			bool useShader = false);

	private:
		void Shader::LoadFromGLSLTextFiles(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
		uint32_t CompileShader(uint32_t type, const std::string& source);

	private:
		uint32_t id = 0;
	};
}