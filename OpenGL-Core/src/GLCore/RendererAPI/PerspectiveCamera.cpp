#include "glpch.h"
#include "PerspectiveCamera.h"

namespace GLCore::RendererAPI 
{

	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: Camera(glm::perspective(fov, aspectRatio, nearClip, farClip))
	{
		UpdateView();
	}

	void PerspectiveCamera::UpdateView()
	{
		m_Position = CalculatePosition();
		glm::quat orientation = GetOrientationQuat();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(transform);
	}

	glm::vec3 PerspectiveCamera::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	glm::quat PerspectiveCamera::GetOrientationQuat() const
	{
		return glm::quat(glm::vec3(-m_Orientation.x, -m_Orientation.y, -m_Orientation.z));
	}

	glm::vec3 PerspectiveCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientationQuat(), glm::vec3(0.0f, 0.0f, -1.0f));
	}
}