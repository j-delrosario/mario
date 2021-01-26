#include "Level.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

void Level::Init()
{
	m_BackgroundTexture = std::make_unique<Texture>("assets/textures/Background.png");
	m_FloorTexture = std::make_unique<Texture>("assets/textures/Floor.png");
	m_TopPillarTexture = std::make_unique<Texture>("assets/textures/TopPipe.png");
	m_BottomPillarTexture = std::make_unique<Texture>("assets/textures/BottomPipe.png");

	m_Pillars.resize(5);
	for (int i = 0; i < 5; i++)
		CreatePillar(i, (i) * 10.0f);
}

void Level::OnUpdate(Timestep ts)
{
}

void Level::OnEvent(Event& e)
{
}

void Level::OnRender()
{
	RendererSpecs rs_Bg = { { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f   }, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, (uint32_t)m_BackgroundTexture->m_TextureID};
	RendererSpecs rs_Floor1 = { { -0.5f, -0.5f, 0.5f }, { 0.5, 0.5 }, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, (uint32_t)m_FloorTexture->m_TextureID};
	RendererSpecs rs_Floor2 = { { -0.25f, -0.25f, 1.0f }, {0.5, 0.5 }, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, (uint32_t)m_FloorTexture->m_TextureID };
	
	Renderer::DrawQuad(rs_Bg);
	Renderer::DrawQuad(rs_Floor1);
	Renderer::DrawQuad(rs_Floor2);

	for (auto& pillar : m_Pillars)
	{
		RendererSpecs rs_TopPillar = { pillar.TopPosition, pillar.TopSize, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, (uint32_t)m_TopPillarTexture->m_TextureID};
		RendererSpecs rs_BottomPillar = { pillar.BottomPosition, pillar.BottomSize, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, (uint32_t)m_BottomPillarTexture->m_TextureID };

		Renderer::DrawQuad(rs_TopPillar);
		Renderer::DrawQuad(rs_BottomPillar);
	}
}

void Level::Reset()
{
	m_GameOver = false;

	m_FloorX1 = -1;
	m_FloorX2 = 1;

	m_PillarTarget = 30.0f;
	m_PillarIndex = 0;
	for (int i = 0; i < m_Pillars.size(); i++)
		CreatePillar(i, (i + 1) * 10.0f);
}

void Level::CreatePillar(int index, float offset)
{
	Pillar& pillar = m_Pillars[index];
	pillar.TopPosition.x = offset;
	pillar.BottomPosition.x = offset;
	pillar.TopPosition.z = 0.1f;
	pillar.BottomPosition.z = 0.2f;

	float center = Random::Float() * 8.0f - 4.0f + FLOOR_HEIGHT;
	float gap = 5.0f;

	pillar.TopPosition.y = center + gap * 0.5f;
	pillar.BottomPosition.y = center - gap * 0.5f;
}