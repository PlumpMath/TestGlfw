#pragma once
#include <string>
#include <glm/vec2.hpp>
#include <glad/glad.h>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H  

class Font
{
public:

	struct Character
	{
		GLuint TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		GLuint Advance;
		char Value;
	};

	static void InitFonts();
	static bool m_IsFTInitialized;

	std::map<char, Character> m_Characters;

	Font();
	~Font();
	void Load(const std::string& ttfPath, int height);

	FT_Face m_Face;
};

