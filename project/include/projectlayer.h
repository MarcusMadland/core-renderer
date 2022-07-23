#pragma once

#include "core.h"

class ProjectLayer : public Core::Layer
{
public:
	ProjectLayer();
	virtual ~ProjectLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(const float& dt) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Core::Event& event) override;
};