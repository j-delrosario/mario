#include "ResourceManager.h"

#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>
using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;
/**
 * Manages the loading and accessing of shared resources.
 */

ResourceManager::ResourceManager()
{
	m_Textures = std::vector<std::shared_ptr<Texture>>();
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::DestroyTextures()
{
	m_Textures.clear();
}

void ResourceManager::LoadFont(const std::string& resourceFilepath)
{
	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF(resourceFilepath.c_str(), 120.0f);
}

void ResourceManager::LoadTextures(const std::vector<std::string>& resourceFilepaths)
{
	for (size_t i = 0; i < resourceFilepaths.size(); i++)
	{
		m_Textures.push_back(std::make_shared<Texture>(resourceFilepaths[i]));
	}
}
