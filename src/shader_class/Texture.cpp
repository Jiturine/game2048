#include "Texture.h"

Texture::Texture(const std::string &path)
	: rendererID(0), filePath(std::string(PATH) + "/" + path), width(0), height(0), BPP(0),
	  localBuffer(nullptr)
{
	stbi_set_flip_vertically_on_load(true); // 用png格式，则要将图片上下翻转
	glGenBuffers(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);
	localBuffer = stbi_load(filePath.c_str(), &width, &height, &BPP, 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	// glBindTexture(GL_TEXTURE_2D, 0);
	if (localBuffer)
	{
		stbi_image_free(localBuffer);
	}
}
Texture ::~Texture()
{
	glDeleteTextures(1, &rendererID);
}
void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}
void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}