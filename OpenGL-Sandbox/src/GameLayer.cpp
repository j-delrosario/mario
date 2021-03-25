#include "GameLayer.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

GameLayer::GameLayer()
    : Layer("GameLayer")
{
    
    CreateGlobals();
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
    CreateCamera();
    m_Camera2->SetPosition({ 0.0f, 0.0f, 0.0f });

    RESOURCE_MANAGER.LoadTextures({ "assets/textures/tiles.png", "assets/textures/characters.png" });
    RESOURCE_MANAGER.LoadFont("assets/OpenSans-Regular.ttf");

    Random::Init();
    m_Level = Level(m_CurrentLevel);
    m_Menu.Init();
    m_LoadingScreen.Init();
}

void GameLayer::OnDetach()
{
    Renderer::EndScene();
    RESOURCE_MANAGER.DestroyTextures();
}

void GameLayer::OnUpdate(Timestep ts)
{
    m_Camera->OnUpdate(ts);
    switch (m_GameState)
    {
    case GameState::MainMenu:
        m_Menu.OnUpdate(ts);
        m_GameState = m_Menu.Exit() ? GameState::LoadingScreen : GameState::MainMenu;
        break;
    case GameState::LoadingScreen:
        m_LoadingScreen.OnUpdate(ts);
        m_GameState = m_LoadingScreen.Exit() ? GameState::Play : GameState::LoadingScreen;
        break;
    case GameState::Play:
        m_Level.OnUpdate(ts);
        if (m_Level.IsGameOver())
        {
            m_GameState = GameState::LoadingScreen;
            m_Level.Restart();
        } 
        else if (m_Level.IsGameOver())
        {
            m_GameState = GameState::MainMenu;
            m_CurrentLevel = 0;
            m_Level = Level(m_CurrentLevel);
        }
        else if (m_Level.IsLevelComplete())
        {
            m_GameState = GameState::LoadingScreen;
            m_CurrentLevel += 1;
            m_Level = Level(m_CurrentLevel);
        }
        break;
    default:
        break;
    }
    Renderer::BeginScene(*m_Camera.get());
    Renderer::Clear();
    Renderer::BeginBatch();
    switch (m_GameState)
    {
    case GameState::MainMenu:
        m_Menu.OnRender();
        break;
    case GameState::LoadingScreen:
        m_LoadingScreen.OnRender();
        break;
    case GameState::Play:
        m_Level.OnRender(ts);
        break;
    default:
        break;
    }

    Renderer::EndBatch();
    Renderer::Flush();
}

void GameLayer::OnImGuiRender()
{
    float x = ImGui::GetWindowPos().x;
    float y = ImGui::GetWindowPos().y;
    std::vector<UIText> uiText = {  {"MARIO", {x, y}, 48.0f},
                                    {"X ", {x + WIN_WIDTH / 4 + WIN_WIDTH / 8, y}, 32.0f},
                                    {"WORLD",  {x + 2 * WIN_WIDTH / 4, y}, 48.0f},
                                    {"TIME", {x + 3 * WIN_WIDTH / 4, y}, 48.0f } };

    switch (m_GameState)
    {
    case GameState::MainMenu:
    {
        uiText.push_back({ "©1985 NINTENDO",{ x, y + WIN_HEIGHT / 4}, 48.0f });
        uiText.push_back({ "START GAME", { x, y + 2 * WIN_HEIGHT / 4 }, 48.0f });
        uiText.push_back({ "TOP- ", { x, y + 3 * WIN_HEIGHT / 4 }, 48.0f });
        uiText.push_back({ std::to_string(m_HiScore), { x + WIN_WIDTH / 4, y + 3 * WIN_HEIGHT / 4 }, 48.0f });
        break;
    }
    case GameState::LoadingScreen:
        uiText.push_back({ "WORLD",  {x + 1.5f * WIN_WIDTH / 4.0f, y + WIN_HEIGHT / 4}, 64.0f });
        uiText.push_back({ LEVELID_TO_WORLDID(m_CurrentLevel),  {x + 2.5f * WIN_WIDTH / 4.0f, y + WIN_HEIGHT / 4}, 64.0f });
        uiText.push_back({ "X ", { x + WIN_WIDTH / 4 + WIN_WIDTH / 8, y + 2 * WIN_HEIGHT / 4 }, 32.0f });
        uiText.push_back({ std::to_string(m_Level.LivesRemaining()), { x + 2 * WIN_WIDTH / 4 + WIN_WIDTH / 8, y + 2 * WIN_HEIGHT / 4 }, 64.0f });
        break;
    default:
        break;
    }
    
    for (size_t i = 0; i < uiText.size(); i++)
    {
        ImGui::GetForegroundDrawList()->AddText(RESOURCE_MANAGER.GetFont(), uiText[i].m_FontSize, uiText[i].m_Position, 0xffffffff, uiText[i].m_Text.c_str());
    }
}

void GameLayer::OnEvent(Event& e)
{
    m_Camera->OnEvent(e); //EDITOR CAMERA ONLY
    switch (m_GameState)
    {
    case GameState::MainMenu:
        m_Menu.OnEvent(e);
        break;
    case GameState::Play:
        m_Level.OnEvent(e);
        break;
    default:
        break;
    }
}


bool GameLayer::OnWindowResize(WindowResizeEvent& e)
{
    return false;
}

void GameLayer::CreateCamera()
{
    m_Camera = std::make_unique<EditorCamera>(45.0f, 0.75f, 0.01f, 1000.0f);
    m_Camera2 = std::make_unique<OrthographicCamera>(-CAM_WIDTH, CAM_WIDTH, -CAM_HEIGHT, CAM_HEIGHT);
}
