#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

class LoadingScreen
{
public:
	LoadingScreen();
	~LoadingScreen();

	void Init();
	void OnUpdate(Timestep ts);
	void OnRender();
	bool Exit();

private:
	std::shared_ptr<Texture> m_Mario;
	glm::vec4 m_MarioTexCoords;
	float m_Time = 0.0f;
	bool m_Exit = false;

	static constexpr float LOADING_SCREEN_TIMEOUT = 1.0f;
};