#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"
#include "Enemy.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

class Goomba : public Enemy
{
public:
	Goomba();
	~Goomba();

	static void Init();

	void OnUpdate(Timestep ts);
	void OnRender(Timestep ts);
	void SetPosition(glm::vec3 position) { m_Position = position; }
	void Kill();
	bool IsAirborne() { return m_Airborne; }
	void SetAirborne() { m_Airborne = true; }
	void SetGrounded();
	void Reverse();
	void Reset();
public:
	static constexpr int WALK_ANIMATION  = 0;
	static constexpr int DEATH_ANIMATION = 1;

	static constexpr int ANIMATION_COUNT = 2;

	static Animation s_Animations[ANIMATION_COUNT];
	static std::shared_ptr<Texture> s_Goomba;
private:
	uint32_t m_CurrentAnimation;
	glm::vec3 m_Position;
	glm::vec2 m_Velocity;
	float m_Time;
	bool m_Airborne;
	bool m_Alive;
private:
	static constexpr glm::vec4 GOOMBA_WALKING_R = { CHAR_SPRITE * 17, 0.8f, CHAR_SPRITE * 18, 0.85f };
	static constexpr glm::vec4 GOOMBA_WALKING_L = { CHAR_SPRITE * 18, 0.8f, CHAR_SPRITE * 19, 0.85f };
	static constexpr glm::vec4 GOOMBA_DYING =     { CHAR_SPRITE * 19, 0.8f, CHAR_SPRITE * 20, 0.85f };
	
	static constexpr float Y_DECELERATION = 0.15f;
};