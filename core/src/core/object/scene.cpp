#include "core/object/scene.h"

#include <windows.h>

#include <glfw/glfw3.h>

#include "core/graphics/shader.h"

namespace Core
{
	Scene::Scene()
	{
		Init();
	}
	Scene::~Scene()
	{
	}

	void Scene::Init()
	{
		// Camera
		camera = new Camera();

		// Shaders
		Shader* shader = Shader::FromGLSL(
			"../core/assets/shaders/core-vert.glsl",
			"../core/assets/shaders/core-frag.glsl");

		Shader* shaderFramebuffer = Shader::FromGLSL(
			"../core/assets/shaders/screen-vert.glsl",
			"../core/assets/shaders/screen-frag.glsl");

		Shader* shaderSkybox = Shader::FromGLSL(
			"../core/assets/shaders/skybox-vert.glsl",
			"../core/assets/shaders/skybox-frag.glsl");

		// Save shaderIDs
		shaderID = shader->GetID();
		screenShaderID = shaderFramebuffer->GetID();
		skyboxShaderID = shaderSkybox->GetID();

		// Create framebuffer
		framebuffer = Framebuffer(screenShaderID);

		// Create skybox
		skybox = Skybox(skyboxShaderID);
	}
	void Scene::Update(float dt)
	{
		PROFILE_SCOPE("Scene");

		framebuffer.Bind();

		{
			PROFILE_SCOPE("Pre-Render");

			// OpenGL settings
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// OpenGL Clear screen
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		// Update camera
		{
			PROFILE_SCOPE("Camera");

			camera->Update(dt, shaderID);
		}
		
		{
			PROFILE_SCOPE("Render");
			PROFILE_SCOPE_ONSCREEN("cpu(render):");

			// Draw all objects in scene
			for (auto& obj : sceneObjects)
			{
				obj->Draw(shaderID);
				for (auto& child : obj->children)
					child->Draw(shaderID);
			}

			// Update skybox
			skybox.Draw(skyboxShaderID, camera->GetPosition(), camera->GetRotation(), camera->GetUpVector());
		}

		framebuffer.Unbind();
	}
	void Scene::OnEvent(Core::Event& event)
	{
		camera->OnEvent(event);
	}

	void Scene::AddObject(Object* object)
	{
		if (object)
			sceneObjects.push_back(object);
	}
}