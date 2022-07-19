#pragma once

#include <windows.h>

#include "object.h"
#include "core/camera/camera.h"
#include "core/events/event.h"

#include "core/graphics/framebuffer.h"
#include "core/graphics/skybox.h"

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

		Camera* GetCamera() { return camera; }

	private:
		Camera* camera;
		std::vector<Object*> sceneObjects;

		Framebuffer framebuffer;
		Skybox skybox;

		uint32_t shaderID = 0;
		uint32_t screenShaderID = 0;
		uint32_t skyboxShaderID = 0;
	};
}