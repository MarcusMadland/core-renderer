#pragma once

#include "object.h"
#include "core/camera/camera.h"

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
		Camera* camera;
		uint32_t shaderID;
	};
}