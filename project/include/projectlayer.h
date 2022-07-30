#pragma once

#include "core.h"

#include "core/layer/layer.h"
#include "core/graphics/shader.h"
#include "core/graphics/camera.h"

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
	Core::Camera camera;

	bool debugMenu;
};