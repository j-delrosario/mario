#include "Level.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

Level::Level()
{
}

Level::Level(uint32_t levelID)
	: m_levelID(levelID)
{
	std::string filepath = LEVELID_TO_BG_FILEPATH(levelID);
	m_Background = std::make_shared<Texture>(filepath);
	m_Player.Init();
	m_Enemies.push_back(new Goomba());
	Goomba::Init();
}

Level::~Level()
{
}

void Level::Init()
{
}

void Level::OnUpdate(Timestep ts)
{
	m_Player.OnUpdate(ts);
	dynamic_cast<Goomba*>(m_Enemies[0])->OnUpdate(ts);
	//loop m_Tiles.OnUpdate(ts);
}

void Level::OnEvent(Event& e)
{
	m_Player.OnEvent(e);
}

void Level::OnRender(Timestep ts)
{
	RendererSpecs rs_Bg = { { 0.0f, 0.0f, 0.0f }, { CAM_WIDTH * 2, CAM_HEIGHT * 2 }, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, (uint32_t)m_Background->m_TextureID , { 0.0f, 0.0f, 0.07547169811f, 1.0f }};
	Renderer::DrawQuad(rs_Bg);

	m_Player.OnRender(ts);
	dynamic_cast<Goomba*>(m_Enemies[0])->OnRender(ts);
	//loop m_Tiles.OnRender();
}

void Level::Restart()
{
	m_Time = 0.0f;
	m_GameOver = false;
	m_LevelComplete = false;
}
