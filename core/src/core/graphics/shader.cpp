#include "core/graphics/shader.h"

#include <vector>
#include <fstream>

namespace Core
{
	static std::string ReadFileAsString(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize((size_t)in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}

		return result;
	}

	Shader::~Shader()
	{
		glDeleteProgram(id);
	}

	Shader* Shader::FromGLSL(const std::string& vertexShaderPath,
		const std::string& fragmentShaderPath)
	{
		Shader* shader = new Shader();
		shader->LoadFromGLSLTextFiles(vertexShaderPath, fragmentShaderPath);
		return shader;
	}

	void Shader::LoadFromGLSLTextFiles(const std::string& vertexShaderPath,
		const std::string& fragmentShaderPath)
	{
		std::string vertexSource = ReadFileAsString(vertexShaderPath);
		std::string fragmentSource = ReadFileAsString(fragmentShaderPath);

		if (vertexSource.empty())
			Logger::LOG(Logger::LogPriority::Error, "Failed to locate Vertex Shader GLSL file.");
		if (fragmentSource.empty())
			Logger::LOG(Logger::LogPriority::Error, "Failed to locate Fragment Shader GLSL file.");

		GLuint program = glCreateProgram();

		GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
		glAttachShader(program, vertexShader);
		GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		id = program;
	}

	GLuint Shader::CompileShader(GLenum type, const std::string& source)
	{
		GLuint shader = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);
		}

		return shader;
	}

	void Shader::Use()
	{
		glUseProgram(id);
	}
}

