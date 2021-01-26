#include "GameLayer.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

GameLayer::GameLayer()
    : Layer("GameLayer")
{
    Window& window = Application::Get().GetWindow();
    CreateCamera();

    //m_Camera->SetPosition({ 0.0f, 0.0f, 0.0f });
    //m_Camera->SetRotation(0.0f);



    Random::Init();

}

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
    m_Level.Init();
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Timestep ts)
{
    Renderer::BeginScene(*m_Camera2.get());
    m_Camera2->OnUpdate(ts);
    Renderer::Clear();


    Renderer::BeginBatch();
    m_Level.OnRender();
    Renderer::EndBatch();
    Renderer::Flush();
}

void GameLayer::OnImGuiRender()
{
}


void GameLayer::OnEvent(Event& e)
{
    //m_Camera2->OnEvent(e);
}


bool GameLayer::OnWindowResize(WindowResizeEvent& e)
{
    m_CamWidth = e.GetWidth();
    m_CamHeight = e.GetHeight();
    CreateCamera();
    return false;
}

void GameLayer::CreateCamera()
{
    //m_Camera = std::make_unique<OrthographicCamera>(-m_CamWidth, m_CamWidth, -m_CamHeight, m_CamHeight);
    m_Camera2 = std::make_unique<EditorCamera>(45.0f, 0.75f, 0.01f, 1000.0f);
    //m_Camera3 = std::make_unique<PerspectiveCamera>(3.14 / 3, 0.75, 0.01, 1000.0);
    //m_Camera3->SetOrientation({ 3.14f / 4, 0.0f, 0.0f });
}
