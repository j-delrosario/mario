#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Event& e) override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
};