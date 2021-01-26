#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

struct Pillar
{
	glm::vec3 TopPosition;
	glm::vec2 TopSize = { 0.5f, 0.5f };

	glm::vec3 BottomPosition;
	glm::vec2 BottomSize = { 0.5f, 0.5f };
};

class Level
{
public:
	void Init();
	void OnUpdate(Timestep ts);
	void OnEvent(Event& e);
	void OnRender();

	bool IsGameOver() const { return m_GameOver; }
	void Reset();
private:
	void CreatePillar(int index, float offset);
	bool CollisionTest();
private:

	bool m_GameOver = false;
	float m_Time = 0.0f;
	
	std::unique_ptr<Texture> m_BackgroundTexture;
	std::unique_ptr<Texture> m_FloorTexture;
	std::unique_ptr<Texture> m_TopPillarTexture;
	std::unique_ptr<Texture> m_BottomPillarTexture;

	int64_t m_FloorX1 = -1;
	int64_t m_FloorX2 =  1;

	int  m_PillarIndex = 0;
	float m_PillarTarget = 30.0f;
	std::vector<Pillar> m_Pillars;
};