#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"

#include "Level.h"
#include "Menu.h"
#include "LoadingScreen.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Event& e) override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;

	bool OnWindowResize(WindowResizeEvent& e);
private:
	void CreateCamera();
private:
	enum class GameState {
		MainMenu = 0,
		LoadingScreen = 1,
		Play = 2,
	};

	Level m_Level;
	Menu m_Menu;
	LoadingScreen m_LoadingScreen;
	uint32_t m_CurrentLevel = 0;
	GameState m_GameState = GameState::MainMenu;
	std::unique_ptr<EditorCamera> m_Camera;
	std::unique_ptr<OrthographicCamera> m_Camera2;
	ImFont* m_Font;
	uint32_t m_HiScore = 0;

	struct UIText {
		std::string m_Text;
		ImVec2 m_Position;
		float m_FontSize;
	};

};