#pragma once
#include <string>
#include <map>
#include "Shader.h"
#include "Texture.h"
#include <memory>

class AssetManager
{
public:
	AssetManager() = default;
	~AssetManager() = default;

	static Shader& LoadShader(const std::string& vertPath, const std::string& fragPath, const std::string& name);
	static Texture* LoadTexture(const std::string& texturePath);
	static Shader& GetShader(const std::string& name);
	static Texture& GetTexture(const std::string& name);
	static void Unload();

	static std::map<std::string, std::unique_ptr<Shader>> m_shaders;
	static std::map<std::string, std::unique_ptr<Texture>> m_textures;
};

