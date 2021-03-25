#include "Player.h"
#include "utils/Animation.h"
using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

Player::Player()
	:m_Lives(3), m_Position(0.0f, 0.0f, 1.0f), m_CurrentAnimation(0), m_Airborne(false), m_Alive(true),
	m_JumpReleased(false), m_JumpMax(false), m_Direction(RIGHT), m_Time(0.0f), m_Velocity({0.0f, 0.0f})
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_Player = RESOURCE_MANAGER.GetTexture(CHAR_TEXTURE_ID);

	m_Animations[STAND_ANIMATION_R].AddFrame(SPRITE_SIZE_S, MARIO_STANDING_R);
	m_Animations[STAND_ANIMATION_L].AddFrame(SPRITE_SIZE_S, MARIO_STANDING_L);

	m_Animations[RUN_ANIMATION_R].AddFrame(SPRITE_SIZE_S, MARIO_RUNNING1_R);
	m_Animations[RUN_ANIMATION_R].AddFrame(SPRITE_SIZE_S, MARIO_RUNNING2_R);
	m_Animations[RUN_ANIMATION_R].AddFrame(SPRITE_SIZE_S, MARIO_RUNNING3_R);

	m_Animations[RUN_ANIMATION_L].AddFrame(SPRITE_SIZE_S, MARIO_RUNNING1_L);
	m_Animations[RUN_ANIMATION_L].AddFrame(SPRITE_SIZE_S, MARIO_RUNNING2_L);
	m_Animations[RUN_ANIMATION_L].AddFrame(SPRITE_SIZE_S, MARIO_RUNNING3_L);

	m_Animations[JUMP_ANIMATION_R].AddFrame(SPRITE_SIZE_S, MARIO_JUMPING_R);
	m_Animations[JUMP_ANIMATION_L].AddFrame(SPRITE_SIZE_S, MARIO_JUMPING_L);

	m_Animations[TURN_ANIMATION_R].AddFrame(SPRITE_SIZE_S, MARIO_TURNING_R);
	m_Animations[TURN_ANIMATION_L].AddFrame(SPRITE_SIZE_S, MARIO_TURNING_L);

	m_Animations[DEATH_ANIMATION].AddFrame(SPRITE_SIZE_S, MARIO_DYING);
}

void Player::OnUpdate(Timestep ts)
{
	if (!m_Alive)
	{
		if (!m_JumpMax)
		{
			m_Velocity.y += Y_ACCELERATION;
			if (m_Velocity.y > DEATH_MAX_Y_VELOCITY)
			{
				m_Velocity.y = DEATH_MAX_Y_VELOCITY;
				m_JumpMax = true;
			}
		}
		
		m_CurrentAnimation = DEATH_ANIMATION;
		m_Airborne = true;
		m_Velocity.y -= Y_DECELERATION;

		m_Position.y += m_Velocity.y * ts;
		return;
	}
	
	if (Input::IsKeyPressed(HZ_KEY_A))
	{
		if (!m_Airborne)
			m_Direction = LEFT;
		m_CurrentAnimation = RUN_ANIMATION_L;
		if (m_Velocity.x > -MAX_X_VELOCITY && m_Velocity.x <= 0)
		{
			m_Velocity.x -= X_ACCELERATION;
		} else if (m_Velocity.x > -MAX_X_VELOCITY && m_Velocity.x > 0)
		{
			m_Velocity.x -= X_SKID_DECELERATION;
			m_CurrentAnimation = TURN_ANIMATION_L;
		}

	}
	else if (Input::IsKeyPressed(HZ_KEY_D))
	{
		if (!m_Airborne)
			m_Direction = RIGHT;
		m_CurrentAnimation = RUN_ANIMATION_R;
		if (m_Velocity.x < MAX_X_VELOCITY && m_Velocity.x >= 0)
		{
			m_Velocity.x += X_ACCELERATION;
		}
		else if (m_Velocity.x < MAX_X_VELOCITY && m_Velocity.x < 0)
		{
			m_Velocity.x += X_SKID_DECELERATION;
			m_CurrentAnimation = TURN_ANIMATION_R;
		}
	}
	else
	{
		if (m_Velocity.x == 0)
		{
			m_CurrentAnimation = m_Direction == RIGHT ? STAND_ANIMATION_R : STAND_ANIMATION_L;
		}
		else
		{
			m_Velocity.x += m_Velocity.x > 0 ? -X_DECELERATION : X_DECELERATION;
			if (m_Velocity.x < MIN_X_VELOCITY && m_Velocity.x > 0)
			{
				m_Velocity.x = 0;
				if (!m_Airborne)
					m_Direction = RIGHT;
				m_CurrentAnimation = STAND_ANIMATION_R;
			}
			else if (m_Velocity.x > -MIN_X_VELOCITY && m_Velocity.x < 0)
			{
				m_Velocity.x = 0;
				if (!m_Airborne)
					m_Direction = LEFT;
				m_CurrentAnimation = STAND_ANIMATION_L;
			}
		}

	}

	if (m_Airborne)
	{
		m_Velocity.y -= Y_DECELERATION;
	}

	if (Input::IsKeyPressed(HZ_KEY_SPACE))
	{
		if (!m_JumpMax && !m_JumpReleased)
		{
			m_Velocity.y += Y_ACCELERATION;
			if (m_Velocity.y > MAX_Y_VELOCITY)
			{
				m_Velocity.y = MAX_Y_VELOCITY;
				m_JumpMax = true;
			}
		}

		m_CurrentAnimation = m_Direction == RIGHT ? JUMP_ANIMATION_R : JUMP_ANIMATION_L;
		m_Airborne = true;
	}
	else
	{
		if (m_Airborne)
		{
			m_CurrentAnimation = m_Direction == RIGHT ? JUMP_ANIMATION_R : JUMP_ANIMATION_L;
			m_JumpReleased = true;
		}
	}

	m_Position.x += m_Velocity.x * ts;
	m_Position.y += m_Velocity.y * ts;

	if (Input::IsKeyPressed(HZ_KEY_ENTER))
		Kill();
}

void Player::OnRender(Timestep ts)
{
	if (m_Time > FRAME_DURATION)
	{
		m_Animations[m_CurrentAnimation].Next();
		m_Time = 0.0f;
	}
	Frame frame = m_Animations[m_CurrentAnimation].GetFrame();
	RendererSpecs rs_Mario = { m_Position, frame.size, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f},
							   (uint32_t)m_Player->m_TextureID , frame.texCoords };
	Renderer::DrawQuad(rs_Mario);
	m_Time += ts;
}

void Player::OnEvent(Event& e)
{
}

void Player::SetAirborne()
{
	m_JumpMax = true; 
	m_Airborne = true;
}

void Player::SetGrounded()
{
	m_Velocity.y = 0; 
	m_JumpMax = false; 
	m_Airborne = false;
}

void Player::Kill()
{
	m_Lives -= m_Lives > 0 ? 1 : 0;
	m_Alive = false;
	m_JumpMax = false;
	m_Velocity.x = 0;
	m_Velocity.y = 0;
}

void Player::Reset()
{
	m_Alive = true; 
	m_Airborne = false; 
	m_JumpMax = false; 
	m_JumpReleased = false; 
	m_Direction = RIGHT;
	m_Time = 0.0f; 
	m_Velocity = { 0.0f, 0.0f }; 
	m_Position = { 0.0f, 0.0f, 1.0f };
}

