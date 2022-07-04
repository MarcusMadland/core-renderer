#include "projectlayer.h"

void ProjectLayer::OnAttach()
{
	// Init here..
	Logger::SetPriority(Logger::LogPriority::Info);

	scene = new Scene();
	scene->Init();

	ImporterGLTF* importer = new ImporterGLTF();
	StaticMeshObject* ryn = 
		importer->ImportStaticMesh("../core/assets/meshes/cube/Cube.gltf");

	scene->AddObject(ryn);
}

void ProjectLayer::OnDetach()
{
	// Shutdown here..
}

void ProjectLayer::OnEvent(Core::Event& event)
{
	// Events here..
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
