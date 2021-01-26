#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

class Level
{
public:
	void Init();
	void OnUpdate(Timestep ts);
	void OnEvent(Event& e);
	void OnRender();

	void Reset();
private:
};