#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"

#include "Level.h"

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
	//std::unique_ptr<OrthographicCamera> m_Camera;
	std::unique_ptr<EditorCamera> m_Camera2;
	//std::unique_ptr<PerspectiveCamera> m_Camera3;
	GameState m_GameState = GameState::MainMenu;
	Level m_Level;

	float m_Time = 0.0f;
	float m_CamWidth = CAM_WIDTH;
	float m_CamHeight = CAM_HEIGHT;
};