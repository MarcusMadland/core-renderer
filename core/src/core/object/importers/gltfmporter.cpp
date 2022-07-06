#include "core/object/importers/gltfimporter.h"

#include <memory>
#include <string>
#include <fstream>

#include "core/debug/logger/logger.h"
#include "core/object/staticmesh.h"

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

	StaticMeshObject* ImporterGLTF::ImportStaticMesh(const char* modelpath)
	{
		if (modelpath == nullptr)
			Logger::LOG(Logger::LogPriority::Error, 
				"Path returned null while trying to import static mesh!");

		// Read gltf file
		std::string text = ReadFileAsString(modelpath);
		json = nlohmann::json::parse(text);

		if (json == nullptr)
			Logger::LOG(Logger::LogPriority::Error, "JSON is returning null!");

		path = modelpath;
		data = GetData();

		if (data.empty())
			Logger::LOG(Logger::LogPriority::Error, "GLTF file contains no data or json was unable to find it! ");

		TraverseNode(0);

		if (!meshes.empty())
			Logger::LOG(Logger::LogPriority::Info, "Successfully imported static mesh object");
		else
			Logger::LOG(Logger::LogPriority::Error, "Static Mesh import failed since gltf file contains no meshes");
		
		return new StaticMeshObject(meshes);
	}

	void ImporterGLTF::LoadMesh(uint32_t indMesh)
	{
		// Positions
		uint32_t posAccInd = json["meshes"][indMesh]\
			["primitives"][0]["attributes"]["POSITION"];
		std::vector<glm::vec3> positions = 
			MakeVec3(GetFloats(json["accessors"][posAccInd]));

		// Normals
		uint32_t norAccInd = json["meshes"][indMesh]\
			["primitives"][0]["attributes"]["NORMAL"];
		std::vector<glm::vec3> normals = 
			MakeVec3(GetFloats(json["accessors"][norAccInd]));

		// Texture UV (TexCoords)
		uint32_t texAccInd = json["meshes"][indMesh]\
			["primitives"][0]["attributes"]["TEXCOORD_0"];
		std::vector<glm::vec2> texUVs =
			MakeVec2(GetFloats(json["accessors"][texAccInd]));

		// Indices
		uint32_t indAccInd = json["meshes"][indMesh]\
			["primitives"][0]["indices"];
		std::vector<uint32_t> indices = 
			GetIndices(json["accessors"][indAccInd]);

		// Make Vertex data and Texture data
		std::vector<Vertex> verts = MakeVertex(positions, normals, texUVs);
		std::vector<Texture> texs = {};

		meshes.push_back(StaticMesh(verts, indices, texs));
	}
	void ImporterGLTF::TraverseNode(uint32_t nextNode)
	{
		nlohmann::json node = json["nodes"][nextNode];

		// Load mesh if we find it
		if (node.find("mesh") != node.end())
			LoadMesh(node["mesh"]);

		// Do the same for all children, if any
		if (node.find("children") != node.end())
		{
			for (uint32_t i = 0; i < node["children"].size(); i++)
				TraverseNode(node["children"][i]);
		}
	}
	std::vector<uint8_t> ImporterGLTF::GetData()
	{
		std::string bytesText;
		std::string uri = json["buffers"][0]["uri"];

		std::string pathStr = std::string(path);
		std::string pathDirectory = pathStr.substr(0, pathStr.find_last_of('/') + 1);
		bytesText = ReadFileAsString((pathDirectory + uri).c_str());

		return std::vector<uint8_t>(bytesText.begin(), bytesText.end());
	}

	std::vector<uint32_t> ImporterGLTF::GetIndices(nlohmann::json accessor)
	{
		std::vector<uint32_t> indices;

		// See page 76 for what values are always found and not always found
		// https://www.khronos.org/registry/glTF/specs/2.0/glTF-2.0.pdf
		uint32_t count = accessor["count"];
		uint32_t componentType = accessor["componentType"];
		uint32_t buffViewInd = accessor.value("bufferView", 1);   // 1 as backup
		uint32_t accByteOffset = accessor.value("byteOffset", 0); // 0 as backup

		nlohmann::json bufferView = json["bufferViews"][buffViewInd];
		uint32_t byteOffset = bufferView["byteOffset"];

		uint32_t beginData = byteOffset + accByteOffset;
		
		// unsigned int
		if (componentType == 5125)
		{
			for (uint32_t i = beginData; 
				i < byteOffset + accByteOffset + count * 4; i)
			{
				// Find value in memory and push back uint for each uint in row
				uint8_t bytes[] = { 
					data[i++], 
					data[i++], 
					data[i++], 
					data[i++] };
				uint32_t value;
				std::memcpy(&value, bytes, sizeof(uint32_t));
				indices.push_back(value);
			}
		}
		// unsigned short
		else if (componentType == 5123)
		{
			for (uint32_t i = beginData;
				i < byteOffset + accByteOffset + count * 2; i)
			{
				// Find value in memory and push back uint for each uint in row
				uint8_t bytes[] = { 
					data[i++], 
					data[i++] };
				uint16_t value;
				std::memcpy(&value, bytes, sizeof(uint16_t));
				indices.push_back(value);
			}
		}
		// signed short
		else if (componentType == 5123)
		{
			for (uint32_t i = beginData;
				i < byteOffset + accByteOffset + count * 2; i)
			{
				// Find value in memory and push back uint for each uint in row
				uint8_t bytes[] = { 
					data[i++], 
					data[i++] };
				int16_t value;
				std::memcpy(&value, bytes, sizeof(int16_t));
				indices.push_back(value);
			}
		}

		return indices;
	}
	std::vector<float> ImporterGLTF::GetFloats(nlohmann::json accessor)
	{
		std::vector<float> floatVec;

		// See page 76 for what values are always found and not always found
		// https://www.khronos.org/registry/glTF/specs/2.0/glTF-2.0.pdf
		uint32_t buffViewInd = accessor.value("bufferView", 1);   // 1 as backup
		uint32_t accByteOffset = accessor.value("byteOffset", 0); // 0 as backup
		uint32_t count = accessor["count"];
		std::string type = accessor["type"];

		nlohmann::json bufferView = json["bufferViews"][buffViewInd];
		uint32_t byteOffset = bufferView["byteOffset"];

		uint32_t numPerVert;
		if (type == "SCALAR")
			numPerVert = 1;
		else if (type == "VEC2")
			numPerVert = 2;
		else if (type == "VEC3")
			numPerVert = 3;
		else if (type == "VEC4")
			numPerVert = 4;
		else
		{
			Logger::LOG(Logger::LogPriority::Error, "GLTF Importer failed to read type (Only types of float, vec2, vec3 and vec4 are supported.)");
			return std::vector<float> {};
		}
			
		uint32_t beginData = byteOffset + accByteOffset;
		uint32_t dataLength = count * 4 * numPerVert;

		for (uint32_t i = beginData; i < beginData + dataLength; i)
		{
			// Find value in memory and push back float for each float in row
			uint8_t bytes[] = { 
				data[i++], 
				data[i++], 
				data[i++], 
				data[i++] };
			float value;
			std::memcpy(&value, bytes, sizeof(float));
			floatVec.push_back(value);
		}

		return floatVec;
	}

	std::vector<glm::vec2> ImporterGLTF::MakeVec2(std::vector<float> val)
	{
		std::vector<glm::vec2> vectors;
		for (uint32_t i = 0; i < val.size(); i)
		{
			vectors.push_back(glm::vec2(val[i++], val[i++]));
		}
		return vectors;
	}
	std::vector<glm::vec3> ImporterGLTF::MakeVec3(std::vector<float> val)
	{
		std::vector<glm::vec3> vectors;
		for (uint32_t i = 0; i < val.size(); i)
		{
			vectors.push_back(glm::vec3(val[i++], val[i++], val[i++]));
		}
		return vectors;
	}
	std::vector<Vertex> ImporterGLTF::MakeVertex(std::vector<glm::vec3> pos, std::vector<glm::vec3> norms, std::vector<glm::vec2> texCoords)
	{
		std::vector<Vertex> verts;
		for (uint32_t i = 0; i < pos.size(); i++)
		{
			verts.push_back(Vertex(pos[i], norms[i], texCoords[i]));
		}

		return verts;
	}
	
}