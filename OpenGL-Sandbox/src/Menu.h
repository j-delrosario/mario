#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

class Menu
{
public:
	Menu();
	~Menu();

	void Init();
	void OnUpdate(Timestep ts);
	void OnEvent(Event& e);
	void OnRender();

	bool Exit() { return exit; }
private:
	bool OnKeyPressed(KeyPressedEvent& e);
private:
	float m_Time = 0.0f;
	std::unique_ptr<Texture> m_Background;
	std::shared_ptr<Texture> m_Mario;
	glm::vec4 m_BgTexCoords;
	glm::vec4 m_MarioTexCoords;

	bool exit = false;
};