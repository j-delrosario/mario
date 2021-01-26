#include "GameLayer.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

GameLayer::GameLayer()
    : Layer("GameLayer")
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Timestep ts)
{
}

void GameLayer::OnImGuiRender()
{
}


void GameLayer::OnEvent(Event& e)
{
}


bool GameLayer::OnWindowResize(WindowResizeEvent& e)
{
    return false;
}

void GameLayer::CreateCamera()
{
}
