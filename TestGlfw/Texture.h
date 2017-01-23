#pragma once
#include <string>
#include <vector>
#include "glad/glad.h"
#include "NonCopyable.h"

class Texture : NonCopyable
{
public:
	Texture();
	~Texture();
	void Load(const std::string& filepath);
	void Bind();
	void Unbind();

	int m_width = 0, m_height = 0, m_channels = 0;
	unsigned char* m_data;
	GLuint m_id;
	
	std::string m_filePath;
};

