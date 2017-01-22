#include "Font.h"
#include <iostream>
#include <fstream>
#include "GLCommon.h"

bool Font::m_IsFTInitialized = false;

void Font::InitFonts()
{
	
	m_IsFTInitialized = true;
}

Font::Font()
{
	/*if(!m_IsFTInitialized)
	{
		std::cout << "Call Font::InitFonts before loading fonts!" << std::endl;
	}*/
}


Font::~Font()
{
}

void Font::Load(const std::string& ttfPath, int height)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	std::ifstream fin(ttfPath.c_str());
	if(fin.fail())
	{
		std::cout << "ERROR::FREETYPE: Font doesn't exist! " << ttfPath << std::endl;
	}

	if (FT_New_Face(ft, ttfPath.c_str(), 0, &m_Face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(m_Face, 0, height);

	if (FT_Load_Char(m_Face, 'X', FT_LOAD_RENDER))
		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;

	GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		GLCall(glGenTextures(1, &texture));
		GLCall(glBindTexture(GL_TEXTURE_2D, texture));
		GLCall(glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			m_Face->glyph->bitmap.width,
			m_Face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			m_Face->glyph->bitmap.buffer
		));
		// Set texture options
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
			glm::ivec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
			m_Face->glyph->advance.x
		};
		m_Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	// Destroy FreeType once we're finished
	FT_Done_Face(m_Face);
	FT_Done_FreeType(ft);
}
