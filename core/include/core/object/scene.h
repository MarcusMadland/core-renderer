#pragma once

#include <windows.h>

#include "object.h"
#include "core/camera/camera.h"
#include "core/events/event.h"

namespace Core
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Init();
		void Update(float dt);
		void OnEvent(Core::Event& event);

		void AddObject(Object* object);

	private:
		std::vector<Object*> sceneObjects;
		Camera* camera;
		uint32_t shaderID;
	};
}