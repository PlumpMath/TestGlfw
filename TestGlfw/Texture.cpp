#include "Texture.h"
#include "Error.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GLCommon.h"

Texture::Texture()
{
	
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_id));
}

void Texture::Load(const std::string& filepath)
{	
	m_filePath = filepath;
	//m_data = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_channels, STBI_rgb_alpha);
	//auto tex = gli::load(filepath);
	/*auto tex = gli::load_dds(filepath);
	gli::texture2D texture(gli::load_dds(filepath));*/
	//gli::gl GL;
	//auto target = GL.translate(tex.target());

	//if (tex.empty())
		//std::cerr << "Error loading stuff\n";

	if(!m_data)
	{
		std::cerr << "failed to load image :" << filepath << ". Reason: " << /*stbi_failure_reason() <<*/ std::endl;;
	}

	GLCall(glGenTextures(1, &m_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	//stbi_image_free(m_data);
}

void Texture::Bind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
