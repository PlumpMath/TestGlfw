#include "Texture.h"
#include "Error.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GLCommon.h"
#include "FreeImage.h"
#include "gliml.h"
#include <fstream>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT                   0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                  0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                  0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                  0x83F3

Texture::Texture()
{
	
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_id));
}

void Texture::Load(const std::string& filepath)
{	
	LoadDDS(filepath);
	return;
	m_filePath = filepath;
	//m_data = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_channels, STBI_rgb_alpha);

	if(!m_data)
	{
		std::cerr << "failed to load image :" << filepath << ". Reason: " << /*stbi_failure_reason() <<*/ std::endl;;
	}

	GLCall(glGenTextures(1, &m_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));

	/*GLCall(glCompressedTexImage2D(GL_TEXTURE_2D, 0, image.get_format(),
		image.get_width(), image.get_height(), 0, image.get_size(),
		image));*/
	//glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA)

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	//stbi_image_free(m_data);
}

void Texture::LoadDDS(const std::string& filepath)
{
	/*// load file into memory (gliml doesn't have any file I/O functions)
	std::ifstream file(filepath, std::ios::in | std::ios::binary);
	file.seekg(0, std::ios::end);
	int size = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector<char> buffer(size);
	file.read(buffer.data(), size);
	file.close();

	gliml::context ctx;
	ctx.enable_dxt(true);
	ctx.enable_pvrtc(true);
	ctx.enable_etc2(true);

	if (ctx.load(&buffer.front(), size)) 
	{
		// create a GL texture
		glGenTextures(1, &m_id);
		glBindTexture(ctx.texture_target(), m_id);

		// set desired texture params
		glTexParameteri(ctx.texture_target(), GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(ctx.texture_target(), GL_TEXTURE_WRAP_T, GL_REPEAT);
		if (ctx.is_3d()) {
			glTexParameteri(ctx.texture_target(), GL_TEXTURE_WRAP_R, GL_REPEAT);
		}
		glTexParameteri(ctx.texture_target(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (ctx.num_mipmaps(0) > 1)
		{
			glTexParameteri(ctx.texture_target(), GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else 
		{
			glTexParameteri(ctx.texture_target(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		// for each (cube-map) face...
		for (int face_index = 0; face_index < ctx.num_faces(); face_index++) {
			// for each mip-map level
			for (int mip_index = 0; mip_index < ctx.num_mipmaps(face_index); mip_index++) {
				if (ctx.is_compressed()) {
					// compressed
					if (ctx.is_2d()) {
						// compressed 2D or cube texture
						glCompressedTexImage2D(ctx.image_target(face_index),
							mip_index,
							ctx.image_internal_format(),
							ctx.image_width(face_index, mip_index),
							ctx.image_height(face_index, mip_index),
							0,
							ctx.image_size(face_index, mip_index),
							ctx.image_data(face_index, mip_index));
					}
					else {
						// compressed 3D texture
						assert(ctx.is_3d());
						glCompressedTexImage3D(ctx.image_target(face_index),
							mip_index,
							ctx.image_internal_format(),
							ctx.image_width(face_index, mip_index),
							ctx.image_height(face_index, mip_index),
							ctx.image_depth(face_index, mip_index),
							0,
							ctx.image_size(face_index, mip_index),
							ctx.image_data(face_index, mip_index));
					}
				}
				else {
					// uncompressed
					if (ctx.is_2d()) {
						// 2D or CUBE texture
						glTexImage2D(ctx.image_target(face_index),
							mip_index,
							ctx.image_internal_format(),
							ctx.image_width(face_index, mip_index),
							ctx.image_height(face_index, mip_index),
							0,
							ctx.image_format(),
							ctx.image_type(),
							ctx.image_data(face_index, mip_index));
					}
					/*else {
						// 3D texture
						assert(ctx.is_3d());
						glTexImage3D(ctx.image_target(face_index),
							mip,
							ctx.image_internal_format(),
							ctx.image_width(face_index, mip_index),
							ctx.image_height(face_index, mip_index),
							ctx.image_depth(face_index, mip_index),
							0,
							ctx.image_format(),
							ctx.image_type(),
							ctx.image_data(face_index, mip_index));
					}#1#
				}
			} // for mip...
		} // for face...
		}*/

	unsigned char header[124];

	FILE *fp;

	//try to open the file #1#
	fp = fopen(filepath.c_str(), "rb");
	if (fp == NULL)
		std::cerr << "ERROR" << std::endl;

	//verify the type of file #1#
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		std::cerr << "ERROR" << std::endl;
	}

	//get the surface desc #1#
	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	m_width = width;
	m_height = height;
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);

	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		std::cerr << "ERROR" << std::endl;
	}


	// Create one OpenGL texture
	GLCall(glGenTextures(1, &m_id));

	// "Bind" the newly created texture : all future texture functions will modify this texture
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
	GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/
	//glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);		

		offset += size;
		width /= 2;
		height /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if (width < 1) width = 1;
		if (height < 1) height = 1;

	}
	
	free(buffer);
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::Bind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
