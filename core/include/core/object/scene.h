#pragma once

#include "object.h"
#include "core/graphics/shader.h"

namespace Core
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Init();
		void Update();
		void AddObject(Object* object);

	private:
		std::vector<Object*> sceneObjects;
		uint32_t shaderID;
	};
}