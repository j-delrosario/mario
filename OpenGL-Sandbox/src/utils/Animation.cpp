#include "Animation.h"

Frame& Animation::GetFrame()
{
	return m_Frames[m_NextFrame];
}

void Animation::Next()
{
	m_NextFrame = ++m_NextFrame % m_Frames.size();
}

Animation::Animation()
	:m_NextFrame(0)
{
}

Animation::Animation(const Animation& animation)
{
	m_NextFrame = animation.m_NextFrame;
	m_Frames = animation.m_Frames;
}

void Animation::AddFrame(glm::vec2 size, glm::vec4 texCoords)
{
	m_Frames.push_back({size, texCoords});
}
