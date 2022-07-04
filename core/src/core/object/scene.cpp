#include "core/object/scene.h"

namespace Core
{
	Scene::Scene()
		: shaderID(0)
	{
	}
	Scene::~Scene()
	{
	}
	void Scene::Init()
	{
		// shader
		Shader* shader = Shader::FromGLSL(
			"../core/assets/shaders/core-vert.glsl", 
			"../core/assets/shaders/core-frag.glsl");
		shaderID = shader->GetID();
	}
	void Scene::Update()
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& obj : sceneObjects)
		{
			obj->Draw(shaderID); // shaderID
			for (auto& child : obj->children)
				child->Draw(shaderID); // shaderID
		}
	}
	void Scene::AddObject(Object* object)
	{
		if (object)
			sceneObjects.push_back(object);
	}
}