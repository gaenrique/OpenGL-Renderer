#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "GL/glew.h"

#include "../Logger/Logger.h"

Texture::Texture(const std::string& filepath, ImageFormat imageFormat)
{
	LoadTextureData(filepath, imageFormat);
	if (!m_RawTextureData)
	{
		Logger::Warn("Texture {} failed to allocate");
		return;
	}
	glGenTextures(1, &m_RendererID);
	Bind();
	// Set the texture wrapping/filtering options of the currently boudn texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Assign the data from jpeg to this texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_RawTextureData);
	// Let OpenGL generate Mipmap
	glGenerateMipmap(m_RendererID);
	// Data can now be freed
	stbi_image_free(m_RawTextureData);
}

void Texture::LoadTextureData(const std::string& filepath, ImageFormat imageFormat)
{
	m_RawTextureData = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_NrChannels, 0);
	if (imageFormat == PNG)
		stbi__vertical_flip(m_RawTextureData, m_Width, m_Height, m_NrChannels);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}