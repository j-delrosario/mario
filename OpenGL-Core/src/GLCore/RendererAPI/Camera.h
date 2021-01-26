#pragma once
#include "glpch.h"

#include <glm/glm.hpp>

namespace GLCore::RendererAPI 
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection) 
			: m_ProjectionMatrix(projection) {}

		const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	protected:
		glm::mat4 m_ProjectionMatrix;
	};
}