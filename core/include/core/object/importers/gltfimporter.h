#pragma once

#include "core/object/importers/importer.h"

#include <vector>

#include <json.h>
#include <glm/glm.hpp>

#include "core/graphics/texture.h"

namespace Core
{
	class ImporterGLTF : public Importer
	{
	public:
		virtual StaticMeshObject* ImportStaticMesh(const char* path) override;

	private:
		void LoadMesh(uint32_t indMesh);
		void TraverseNode(uint32_t nextNode);
		std::vector<uint8_t> GetData();

		std::vector<uint32_t> GetIndices(nlohmann::json accessor);
		std::vector<float> GetFloats(nlohmann::json accessor);
		std::vector<Texture> GetTextures(uint32_t indMesh);

		std::vector<glm::vec2> MakeVec2(std::vector<float> val);
		std::vector<glm::vec3> MakeVec3(std::vector<float> val);
		std::vector<Vertex> MakeVertex(std::vector<glm::vec3> pos,
			std::vector<glm::vec3> norms, std::vector<glm::vec2> texCoords);

	private:
		const char* path;
		nlohmann::json JSON;
		std::vector<uint8_t> data;
		std::vector<StaticMesh> meshes;

		std::vector<std::string> loadedTexPath;
		std::vector<Texture> loadedTextures;
	};
}