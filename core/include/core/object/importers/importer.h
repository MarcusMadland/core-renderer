#pragma once

#include "core/object/staticmesh.h"

namespace Core
{
	class Importer
	{
	public:
		virtual StaticMeshObject* ImportStaticMesh(const char* path) = 0;
	};
}