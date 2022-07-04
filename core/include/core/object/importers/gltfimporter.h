#pragma once

#include <tiny_gltf.h>

#include "core/object/importer.h"

namespace Core
{
	class ImporterGLTF : public Importer
	{
	public:
		virtual StaticMeshObject* ImportStaticMesh(const char* path) override;
	};
}