#pragma once
#
#include "GLCore/Core/Timestep.h"
#include "../Events/Event.h"
#include "OrthographicCamera.h"
#include "EditorCamera.h"
#include "PerspectiveCamera.h"
#include <glm/glm.hpp>

namespace GLCore::RendererAPI {
	struct RendererSpecs
	{
		const glm::vec3& position = {0.0f, 0.0f, 0.0f};
		const glm::vec2& size = {1.0f, 1.0f};
		float rotation = 0.0f;
		const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f };
		uint32_t textureID = 0;
		const glm::vec4& texCoords = {0.0f, 0.0f, 1.0f, 1.0f};
	};

	// 2D Batch Renderer
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		// New camera update functions
		static void BeginScene(const OrthographicCamera& camera);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();

		static void BeginBatch();
		static void EndBatch();
		static void Flush();

		static void DrawQuad(const RendererSpecs& rSpecs);

		static void SetClearColor(const glm::vec4& color);
		static void Clear();
		static void DisableBlend();

		static void SetUniformMat4(uint32_t shader, const char* name, const glm::mat4& matrix);
	private:
		static void UpdateQuadBuffer(const glm::vec3& position, const glm::vec4& color, const glm::vec2& texCoords, float textureIndex);
		static float TexIDtoTexIndex(uint32_t textureID);
		static glm::vec4 Center(const glm::vec2& position, const glm::vec2& size);
		static glm::vec2 Rotate(const glm::vec2& point, float rotation);
	};
}