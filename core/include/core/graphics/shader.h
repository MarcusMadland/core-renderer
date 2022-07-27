#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Core
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		static Shader* FromGLSL(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
		void Bind() const;
		void Unbind() const;

		void UniformMat4(const char* name, const glm::mat4& matrix);

		uint32_t GetID() const { return id; }

	private:
		void Shader::LoadFromGLSLTextFiles(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
		uint32_t CompileShader(uint32_t type, const std::string& source);

	private:
		uint32_t id;
	};
}