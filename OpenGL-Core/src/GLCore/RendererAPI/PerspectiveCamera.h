#pragma once
#include "Camera.h"

#include <glm/gtx/quaternion.hpp>

namespace GLCore::RendererAPI {

	class PerspectiveCamera : public Camera 
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; UpdateView();}

		inline float GetDistance() const { return m_Distance;  }
		inline void SetDistance(float distance) { m_Distance = distance; UpdateView();}

		const glm::vec3& GetOrientation() const { return m_Orientation; }
		void SetOrientation(const glm::vec3& orientation) { m_Orientation = orientation; UpdateView(); }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4 GetViewProjectionMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; }
	private:
		void UpdateView();
		glm::vec3 CalculatePosition() const;
		glm::quat GetOrientationQuat() const;
		glm::vec3 GetForwardDirection() const;
	private:
		float m_Distance = 10.0f;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Orientation = { 0.0f, 0.0f, 0.0f };

		glm::mat4 m_ViewMatrix;
	};

}