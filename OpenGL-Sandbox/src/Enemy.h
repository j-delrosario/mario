#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

class Enemy
{
public:
	static void Init();

	virtual void OnUpdate(Timestep ts) = 0;
	virtual void OnRender(Timestep ts) = 0;
	virtual void Kill() = 0;
	virtual void Reset() = 0;
};