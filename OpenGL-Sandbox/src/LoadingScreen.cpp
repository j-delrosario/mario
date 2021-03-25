#include "LoadingScreen.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

LoadingScreen::LoadingScreen()
{
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::Init()
{
	m_Mario = RESOURCE_MANAGER.GetTexture(CHAR_TEXTURE_ID);
	m_MarioTexCoords = { 0.54f, 0.84f, 0.566f, 0.91f };
}

void LoadingScreen::OnUpdate(Timestep ts)
{
	m_Time += ts;
	if (m_Time > LOADING_SCREEN_TIMEOUT)
	{
		m_Exit = true;
	}
}

void LoadingScreen::OnRender()
{
	RendererSpecs rs_BgBlack = { { 0.0f, 0.0f, 0.0f }, { CAM_WIDTH * 2, CAM_HEIGHT * 2 }, 0.0f, {0.0f, 0.0f, 0.0f, 1.0f}, 0.0f , { 0.0f, 0.0f, 0.0f, 0.0f } };
	RendererSpecs rs_Mario = { { -CAM_WIDTH + 0.4f, -CAM_HEIGHT + 0.4f, 0.1f }, { 0.12 * 2, 0.16 * 2 }, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, (uint32_t)m_Mario->m_TextureID , m_MarioTexCoords };
	Renderer::DrawQuad(rs_BgBlack);
	Renderer::DrawQuad(rs_Mario);
}

bool LoadingScreen::Exit()
{
	if (m_Exit)
	{
		m_Exit = false;
		m_Time = 0.0f;
		return true;
	}
	return false;
}
