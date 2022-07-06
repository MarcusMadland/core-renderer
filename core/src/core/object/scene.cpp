#include "core/object/scene.h"

#include <iostream>

#include "core/graphics/shader.h"

namespace Core
{
	Scene::Scene()
		: shaderID(0)
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

		// Shader
		Shader* shader = Shader::FromGLSL(
			"../core/assets/shaders/core-vert.glsl",
			"../core/assets/shaders/core-frag.glsl");
		shader->Use();

		// Save shaderID
		shaderID = shader->GetID();
	}
	void Scene::Update()
	{
		// Clear screen
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update camera
		camera->Update(shaderID);

		// Draw all objects in scene
		for (auto& obj : sceneObjects)
		{
			obj->Draw(shaderID); 
			for (auto& child : obj->children)
				child->Draw(shaderID); 
		}
	}

	void Scene::AddObject(Object* object)
	{
		if (object)
			sceneObjects.push_back(object);
	}
}