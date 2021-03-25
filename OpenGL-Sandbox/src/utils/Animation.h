#pragma once

#include <GLCore.h>

struct Frame
{
	glm::vec2 size;
	glm::vec4 texCoords;
};

class Animation
{
public:
	Animation();
	Animation(const Animation& animation);
	void AddFrame(glm::vec2 size, glm::vec4 texCoords);
	void Next();
	void Reset() { m_NextFrame = 0; }
	Frame& GetFrame();
	size_t GetFrameCount() { return m_Frames.size(); }
public:
	std::vector<Frame> m_Frames;
	uint32_t m_NextFrame;
};