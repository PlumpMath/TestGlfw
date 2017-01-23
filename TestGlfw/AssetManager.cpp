#include "AssetManager.h"

std::map<std::string, std::unique_ptr<Shader>> AssetManager::m_shaders;
std::map<std::string, std::unique_ptr<Texture>> AssetManager::m_textures;

Shader& AssetManager::LoadShader(const std::string& vertPath, const std::string& fragPath, const std::string& name)
{
	if(m_shaders.count(name) == 0)
	{
		m_shaders.insert({ name, std::move(std::make_unique<Shader>()) });
		//m_shaders[name] = Shader();
		m_shaders[name]->Load(vertPath, fragPath);
		m_shaders[name]->m_name = name;
	}
	return *m_shaders[name];
}

Texture* AssetManager::LoadTexture(const std::string& texturePath)
{
	if (m_textures.count(texturePath) == 0)
	{
		m_textures.insert({ texturePath, std::move(std::make_unique<Texture>()) });
		m_textures[texturePath]->Load(texturePath);
	}
	return m_textures[texturePath].get();
}

Shader& AssetManager::GetShader(const std::string& name)
{
	return *m_shaders.find(name)->second.get();
}

Texture& AssetManager::GetTexture(const std::string& name)
{
	return *m_textures[name];
}

void AssetManager::Unload()
{
	m_shaders.clear();
	m_textures.clear();
}
