#include "Goomba.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

Animation Goomba::s_Animations[ANIMATION_COUNT];
std::shared_ptr<Texture> Goomba::s_Goomba;

Goomba::Goomba ()
	:m_CurrentAnimation(0), m_Position({0.0f, 0.0f, 1.0f}), m_Velocity({ 2.0f, 0.0f }), m_Time(0.0f)
{
}

Goomba::~Goomba()
{
}

void Goomba::Init()
{
	Goomba::s_Goomba = RESOURCE_MANAGER.GetTexture(CHAR_TEXTURE_ID);

	Goomba::s_Animations[WALK_ANIMATION].AddFrame(SPRITE_SIZE_S, GOOMBA_WALKING_R);
	Goomba::s_Animations[WALK_ANIMATION].AddFrame(SPRITE_SIZE_S, GOOMBA_WALKING_L);

	Goomba::s_Animations[DEATH_ANIMATION].AddFrame(SPRITE_SIZE_S, GOOMBA_DYING);
}

void Goomba::OnUpdate(Timestep ts)
{
	if (!m_Alive)
	{
		m_CurrentAnimation = DEATH_ANIMATION;
		return;
	}

	if (m_Airborne)
	{
		m_Velocity.y -= Y_DECELERATION;
	}

	m_Position.x += m_Velocity.x * ts;
	m_Position.y += m_Velocity.y * ts;
}

void Goomba::OnRender(Timestep ts)
{
	if (m_Time > FRAME_DURATION)
	{
		s_Animations[m_CurrentAnimation].Next();
		m_Time = 0.0f;
	}
	Frame frame = s_Animations[m_CurrentAnimation].GetFrame();
	RendererSpecs rs_Goomba = { m_Position, frame.size, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f},
							   (uint32_t)s_Goomba->m_TextureID , frame.texCoords };
	Renderer::DrawQuad(rs_Goomba);
	m_Time += ts;
}

void Goomba::Kill()
{
	m_Alive = false;
	m_Velocity.x = 0;
}

void Goomba::SetGrounded()
{
	m_Airborne = false;
	m_Velocity.y = 0;
}

void Goomba::Reverse()
{
	m_Velocity.x = -m_Velocity.x;
}

void Goomba::Reset()
{
	m_Velocity.x = 0.0f;
}
