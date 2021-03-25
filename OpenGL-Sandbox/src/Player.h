#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>

#include "Defines.h"

using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;

class Player
{
public:
	Player();
	~Player();

	void Init();
	void OnUpdate(Timestep ts);
	void OnRender(Timestep ts);
	void OnEvent(Event& e);

	uint32_t GetLives() { return m_Lives; }
	const glm::vec3& GetPosition() const { return m_Position; }
	bool IsAirborne() { return m_Airborne; }
	void SetAirborne();
	void SetGrounded();
	void Kill();
	void Reset();
private:
	static constexpr int STAND_ANIMATION_R = 0;
	static constexpr int STAND_ANIMATION_L = 1;
	static constexpr int RUN_ANIMATION_R = 2;
	static constexpr int RUN_ANIMATION_L = 3;
	static constexpr int JUMP_ANIMATION_R = 4;
	static constexpr int JUMP_ANIMATION_L = 5;
	static constexpr int TURN_ANIMATION_R = 6;
	static constexpr int TURN_ANIMATION_L = 7;
	static constexpr int DEATH_ANIMATION = 8;

	static constexpr int ANIMATION_COUNT = 9;

	static constexpr int LEFT = 0;
	static constexpr int RIGHT = 1;
private:
	Animation m_Animations[ANIMATION_COUNT];
	uint32_t m_CurrentAnimation;
	std::shared_ptr<Texture> m_Player;

	uint32_t m_Lives;
	glm::vec3 m_Position;

	bool m_Alive;
	bool m_Airborne;
	bool m_JumpReleased;
	bool m_JumpMax;
	float m_Direction;
	float m_Time;
	glm::vec2 m_Velocity;

private:
	static constexpr float MIN_X_VELOCITY = 0.3f;
	static constexpr float MIN_Y_VELOCITY = 0.05f;

	static constexpr float MAX_X_VELOCITY = 1.5f;
	static constexpr float MAX_Y_VELOCITY = 4.0f;
	static constexpr float DEATH_MAX_Y_VELOCITY = 3.0f;

	static constexpr float X_ACCELERATION = 0.05f;
	static constexpr float X_DECELERATION = 0.10f;
	static constexpr float X_SKID_DECELERATION = 0.05f;

	static constexpr float Y_ACCELERATION = 0.5f;
	static constexpr float Y_DECELERATION = 0.15f;

	static constexpr glm::vec2 MARIO_SIZE_L = { 0.16 * 2, 0.24 * 2 };

	static constexpr double unit = 1 / 32.0f;
	static constexpr double unitY = 1 / 25.0f;

	static constexpr glm::vec4 MARIO_STANDING_R  = { unit * 16, 0.85f, unit * 17, 0.9f };
	static constexpr glm::vec4 MARIO_RUNNING1_R  = { unit * 17, 0.85f, unit * 18, 0.9f };
	static constexpr glm::vec4 MARIO_RUNNING2_R  = { unit * 18, 0.85f, unit * 19, 0.9f };
	static constexpr glm::vec4 MARIO_RUNNING3_R  = { unit * 19, 0.85f, unit * 20, 0.9f };
	static constexpr glm::vec4 MARIO_TURNING_R   = { unit * 20, 0.85f, unit * 21, 0.9f };
	static constexpr glm::vec4 MARIO_JUMPING_R   = { unit * 21, 0.85f, unit * 22, 0.9f };

	static constexpr glm::vec4 MARIO_STANDING_L  = { unit * 15, 0.85f, unit * 16, 0.9f };
	static constexpr glm::vec4 MARIO_RUNNING1_L  = { unit * 14, 0.85f, unit * 15, 0.9f };
	static constexpr glm::vec4 MARIO_RUNNING2_L  = { unit * 13, 0.85f, unit * 14, 0.9f };
	static constexpr glm::vec4 MARIO_RUNNING3_L  = { unit * 12, 0.85f, unit * 13, 0.9f };
	static constexpr glm::vec4 MARIO_TURNING_L   = { unit * 11, 0.85f, unit * 12, 0.9f };
	static constexpr glm::vec4 MARIO_JUMPING_L   = { unit * 10, 0.85f, unit * 11, 0.9f };

	static constexpr glm::vec4 MARIO_DYING       = { unit * 29, 0.85f, unit * 30, 0.9f };

};