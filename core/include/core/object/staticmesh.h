#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "object.h"

namespace Core
{
	struct Vertex
	{
		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords)
			: position(position)
			, normal(normal)
			, texCoords(texCoords)
		{}

		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	struct Texture
	{
		uint32_t rendererID;
	};

	struct StaticMesh
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		uint32_t vao;
		uint32_t vbo;
		uint32_t ebo;

		StaticMesh()
			: vao(0), vbo(0), ebo(0)
		{}
		StaticMesh(
			std::vector<Vertex> vertices, 
			std::vector<unsigned int> indices,
			std::vector<Texture> textures);

		void Draw(uint32_t shaderID);
	};

	class StaticMeshObject : public Object
	{
	public:
		StaticMeshObject(std::vector<StaticMesh> meshes)
			: meshes(meshes)
		{}

		virtual void Draw(uint32_t shaderID) override;

	private:
		std::vector<StaticMesh> meshes;
	};
}