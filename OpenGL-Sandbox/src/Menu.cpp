#include "Menu.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Init()
{
	std::string filepath = LEVELID_TO_BG_FILEPATH(0);
	m_Background = std::make_unique<Texture>(filepath);
	m_Mario = RESOURCE_MANAGER.GetTexture(CHAR_TEXTURE_ID);
	m_BgTexCoords = { 0.0f, 0.0f, 0.07547169811f, 1.0f };
	m_MarioTexCoords = { 0.54f, 0.84f, 0.566f, 0.91f };
}

void Menu::OnUpdate(Timestep ts)
{
}

void Menu::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<KeyPressedEvent>(GLCORE_BIND_EVENT_FN(Menu::OnKeyPressed));
}

bool Menu::OnKeyPressed(KeyPressedEvent& e)
{
	if (e.GetKeyCode() == HZ_KEY_ENTER)
	{
		exit = true;
	}
	return false;
}

void Menu::OnRender()
{
	RendererSpecs rs_Bg = { { 0.0f, 0.0f, 0.0f }, { CAM_WIDTH * 2, CAM_HEIGHT * 2 }, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, (uint32_t)m_Background->m_TextureID , m_BgTexCoords };
	RendererSpecs rs_Mario = { { -CAM_WIDTH + 0.4f, -CAM_HEIGHT+0.4f, 0.1f }, { 0.12*2, 0.16*2 }, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, (uint32_t)m_Mario->m_TextureID , m_MarioTexCoords };
	Renderer::DrawQuad(rs_Bg);
	Renderer::DrawQuad(rs_Mario);
}