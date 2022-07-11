#include "projectlayer.h"

#include "core/debug/instrumentor.h"

void ProjectLayer::OnAttach()
{
	// Init here..
	Logger::SetPriority(Logger::LogPriority::Info);

	scene = new Scene();

	ImporterGLTF* importer = new ImporterGLTF();

	StaticMeshObject* rabbit = importer->ImportStaticMesh(
		"../core/assets/meshes/bunny/scene.gltf");
	rabbit->SetObjectScale({ 2.0f, 2.0f, 2.0f });
	rabbit->SetObjectRotation({ 0.0f, 90.0f, -90.0f });

	for (uint32_t i = 0; i < 10; i++)
	{
		for (uint32_t j = 0; j < 10; j++)
		{
			for (uint32_t k = 0; k < 5; k++)
			{
				StaticMeshObject* newRabbit = new StaticMeshObject(*rabbit);
				newRabbit->SetObjectPosition({ -1.0f * i, -1.0f * j, -1.0f * k });
				scene->AddObject(newRabbit);
			}
		}
	}
}

void ProjectLayer::OnDetach()
{
	// Shutdown here..
}

void ProjectLayer::OnEvent(Core::Event& event)
{
	// Events here..
	scene->OnEvent(event);
}

void ProjectLayer::OnUpdate(const float& dt)
{
	// Update here..
	PROFILE_SCOPE_ONSCREEN("cpu(project):");
	scene->Update(dt);
}

void ProjectLayer::OnImGuiRender()
{
	// ImGui here..	
	
}
