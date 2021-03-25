#include "Koopa.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

Animation Koopa::s_Animations[ANIMATION_COUNT];
std::shared_ptr<Texture> Koopa::s_Koopa;

Koopa::Koopa()
	:m_CurrentAnimation(0), m_Position({ 0.0f, 0.0f, 1.0f }), m_Velocity({ 2.0f, 0.0f }), m_Time(0.0f)
{
}

Koopa::~Koopa()
{
}

void Koopa::Init()
{
	Koopa::s_Koopa = RESOURCE_MANAGER.GetTexture(CHAR_TEXTURE_ID);

	Koopa::s_Animations[WALK_ANIMATION].AddFrame(SPRITE_SIZE_S, KOOPA_WALKING1_R);
	Koopa::s_Animations[WALK_ANIMATION].AddFrame(SPRITE_SIZE_S, KOOPA_WALKING1_L);

	Koopa::s_Animations[DEATH_ANIMATION].AddFrame(SPRITE_SIZE_S, KOOPA_DYING);
}

void Koopa::OnUpdate(Timestep ts)
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

void Koopa::OnRender(Timestep ts)
{
	if (m_Time > FRAME_DURATION)
	{
		s_Animations[m_CurrentAnimation].Next();
		m_Time = 0.0f;
	}
	Frame frame = s_Animations[m_CurrentAnimation].GetFrame();
	RendererSpecs rs_Koopa = { m_Position, frame.size, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f},
							   (uint32_t)s_Koopa->m_TextureID , frame.texCoords };
	Renderer::DrawQuad(rs_Koopa);
	m_Time += ts;
}

void Koopa::Kill()
{
	m_Alive = false;
	m_Velocity.x = 0;
}

void Koopa::SetGrounded()
{
	m_Airborne = false;
	m_Velocity.y = 0;
}

void Koopa::Reverse()
{
	m_Velocity.x = -m_Velocity.x;
}

void Koopa::Reset()
{
	m_Velocity.x = 0.0f;
}
