#pragma once

#include "core.h"

#include "core/layer/layer.h"
#include "core/graphics/camera_controller.h"
#include "core/events/key_event.h"
#include "core/graphics/renderer_command.h"
#include "core/graphics/renderer.h"
#include "core/graphics/shader.h"

class ProjectLayer : public Core::Layer
{
public:
	ProjectLayer() = default;
	virtual ~ProjectLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(const float& dt) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Core::Event& event) override;

private:
	Core::CameraController camera;

	bool debugMenu;

	// temp data
	float vertices[3 * 8] =
	{ 
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f
	};
	uint32_t indices[12 * 3] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};
	Core::Ref<Core::VertexBuffer> vbo;
	Core::Ref<Core::IndexBuffer> ibo;
	Core::Ref<Core::VertexArray> vao;
	Core::Ref<Core::Shader> shader;
	glm::vec3 cubePos;
};