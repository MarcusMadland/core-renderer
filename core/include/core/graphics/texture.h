#pragma once

#include <memory>

namespace Core
{
	class Texture
	{
	public:
		uint32_t id;
		const char* type;
		uint32_t unit;

		Texture() = default;
		Texture(const char* image, const char* texType, uint32_t slot);
		void TexUnit(uint32_t shaderID, const char* uniform, uint32_t unit);

		void Bind();
		void Unbind();
		void Delete();
	};
}