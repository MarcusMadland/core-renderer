#include "projectlayer.h"

void ProjectLayer::OnAttach()
{
	// Init here..
	Logger::SetPriority(Logger::LogPriority::Info);

	scene = new Scene();

	ImporterGLTF* importer = new ImporterGLTF();

	StaticMeshObject* rabbit = importer->ImportStaticMesh(
		"../core/assets/meshes/bunny/scene.gltf");
	rabbit->SetObjectScale({ 2.0f, 2.0f, 2.0f });
	rabbit->SetObjectPosition({ 0.0f, -0.2f, -0.3f });
	rabbit->SetObjectRotation({ 0.0f, 90.0f, -90.0f });

	scene->AddObject(rabbit);
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
	scene->Update();
}

void ProjectLayer::OnImGuiRender()
{
	// ImGui here..	
	ImGuiEx::ShowFPS();
}
