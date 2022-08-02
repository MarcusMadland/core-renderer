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

#include "core/graphics/opengl/ogl_shader.h"

#include <vector>
#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Core
{
	OpenGLShader::OpenGLShader(const std::string& vertexShaderPath,
		const std::string& fragmentShaderPath)
		: id(0)
	{
		// Read file as string for Vertex Shader
		std::string vertexSource;
		std::ifstream vertexIn(vertexShaderPath, std::ios::in | std::ios::binary);
		if (vertexIn)
		{
			vertexIn.seekg(0, std::ios::end);
			vertexSource.resize((size_t)vertexIn.tellg());
			vertexIn.seekg(0, std::ios::beg);
			vertexIn.read(&vertexSource[0], vertexSource.size());
			vertexIn.close();
		}
		else
			std::cout << "vertexShaderPath: Shader not found" << std::endl;

		// Read file as string for Fragment Shader
		std::string fragmentSource;
		std::ifstream fragIn(fragmentShaderPath, std::ios::in | std::ios::binary);
		if (fragIn)
		{
			fragIn.seekg(0, std::ios::end);
			fragmentSource.resize((size_t)fragIn.tellg());
			fragIn.seekg(0, std::ios::beg);
			fragIn.read(&fragmentSource[0], fragmentSource.size());
			fragIn.close();
		}
		else
			std::cout << "fragmentShaderPath: Shader not found" << std::endl;

		// Create and Compile OpenGL shader
		GLuint program = glCreateProgram();

		GLuint vertexShader = Compile(GL_VERTEX_SHADER, vertexSource);
		glAttachShader(program, vertexShader);
		GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSource);
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

		// Extract and set name from filepath
		auto lastSlash = vertexShaderPath.find_last_of("/\\");
		lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;

		auto lastDot = vertexShaderPath.rfind('-');
		auto count = (lastDot == std::string::npos) ? vertexShaderPath.size() - lastSlash : lastDot - lastSlash;

		name = vertexShaderPath.substr(lastSlash, count);
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(id);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(id);
	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UniformMat4(const char* name, const glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UniformVec4(const char* name, const glm::vec4& value)
	{
		glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
	}

	uint32_t OpenGLShader::Compile(uint32_t type, const std::string& source)
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
}