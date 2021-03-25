#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"

#include "Player.h"
#include "Block.h"
#include "Enemy.h"
#include "Goomba.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

class Level
{
public:
	Level();
	Level(uint32_t levelID);
	~Level();

	void Init();
	void OnUpdate(Timestep ts);
	void OnEvent(Event& e);
	void OnRender(Timestep ts);

	void Restart();

	bool IsGameOver() { return m_GameOver; }
	bool IsLevelComplete() { return m_LevelComplete; }
	uint32_t LivesRemaining() { return m_Player.GetLives(); }
private:
	uint32_t m_levelID;
	std::shared_ptr<Texture> m_BackgroundTexture;
	float m_Time = 0.0f;
	Player m_Player;
	std::vector<Block*> m_Blocks;
	std::vector<Enemy*> m_Enemies;
	std::shared_ptr<Texture> m_Background;
	bool m_GameOver = false;
	bool m_LevelComplete = false;
};