#include "projectlayer.h"

#include "core/graphics/renderer_command.h"
#include "core/graphics/renderer.h"

void ProjectLayer::OnAttach()
{
	// Init here..

	camera = Core::Camera(90.0f, 1280.0f, 720.0f, 0.1f, 500.0f);
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

	Core::RendererCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
	Core::RendererCommand::Clear();

	Core::Renderer::BeginScene(camera);
	Core::Renderer::EndScene();
}

void ProjectLayer::OnImGuiRender()
{
	// ImGui here..	
}
