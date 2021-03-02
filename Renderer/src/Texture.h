#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind() const;
	void Unbind() const;

	inline int GetTextureWidth() { return m_Width; }
	inline int GetTextureHeight() { return m_Height; }

private:

	void LoadTextureData(const std::string& filepath);

	unsigned int m_RendererID;
	unsigned char* m_RawTextureData;
	int m_Width, m_Height, m_NrChannels;
};
