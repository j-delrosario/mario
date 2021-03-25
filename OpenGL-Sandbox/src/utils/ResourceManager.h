#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <GLCore.h>
#include <GLCoreUtils.h>
#include <GLCoreRendererAPI.h>
using namespace GLCore;
using namespace GLCore::Utils;
using namespace GLCore::RendererAPI;
/**
 * Manages the loading and accessing of shared resources.
 */
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void LoadTextures(const std::vector<std::string>& resourceFilepaths);
	void DestroyTextures();

	void LoadFont(const std::string& resourceFilepath);

	std::shared_ptr<Texture> GetTexture(int i) { return m_Textures[i]; }
	const ImFont* GetFont() { return m_Font; }
private:
	std::vector<std::shared_ptr<Texture>> m_Textures;
	ImFont* m_Font;
};

#endif