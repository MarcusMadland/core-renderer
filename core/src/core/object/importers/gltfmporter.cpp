#include "core/object/importers/gltfimporter.h"

#include <string>

#include "core/debug/logger/logger.h"
#include "core/object/staticmesh.h"

namespace Core
{
	StaticMeshObject* ImporterGLTF::ImportStaticMesh(const char* path)
	{
		std::vector<StaticMesh> meshes;

		// Tiny GLTF loading and checks
		tinygltf::TinyGLTF loader;
		tinygltf::Model model;
		std::string err;
		std::string warn;

		bool result = loader.LoadASCIIFromFile(&model, &err, &warn, path);

		if (!warn.empty()) 
			Logger::LOG(Logger::LogPriority::Error, warn.c_str());

		if (!err.empty()) 
			Logger::LOG(Logger::LogPriority::Critical, err.c_str());

		if (!result)
			Logger::LOG(Logger::LogPriority::Error, 
				"Failed to load StaticMeshObject at: %s", path);

		else
			Logger::LOG(Logger::LogPriority::Info,
				"Loaded Object: %s", path);

		for (uint32_t i = 0; i < model.accessors.size(); i++)

		// Process all meshes and add them to meshes
		for (uint32_t i = 0; i < model.meshes.size(); i++)
		{
			
		}

		return nullptr;
	}
	
}