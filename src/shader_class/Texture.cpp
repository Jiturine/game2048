#include "Texture.h"

Texture::Texture(const std::string &path)
	: rendererID(0), width(0), height(0), BPP(0)
{
	stbi_set_flip_vertically_on_load(true); // 用png格式，则要将图片上下翻转
	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	std::filesystem::path rootPath(PATH);
	auto str = (rootPath / path).string();
	const char *cstr = str.c_str();
	auto localBuffer = stbi_load(cstr, &width, &height, &BPP, 0);
	if (localBuffer)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(localBuffer);
	}
	else
	{
		LOG_INFO(str);
		LOG_ERROR("Failed to load texture! Reason:{}", stbi_failure_reason());
	}
}
Texture::Texture(const Texture &texture)
	: width(texture.width), height(texture.height), BPP(texture.BPP)
{
	glGenTextures(1, &rendererID);
	glCopyImageSubData(
		texture.rendererID, GL_TEXTURE_2D, 0, 0, 0, 0, // 源纹理和位置
		rendererID, GL_TEXTURE_2D, 0, 0, 0, 0,		   // 目标纹理和位置
		width, height, 1							   // 尺寸
	);
}
Texture::~Texture()
{
	glDeleteTextures(1, &rendererID);
}
Texture::Texture(Texture &&texture) noexcept
	: Texture()
{
	swap(texture, *this);
}
Texture &Texture::operator=(Texture texture)
{
	swap(texture, *this);
	return *this;
}
void swap(Texture &texture_1, Texture texture_2)
{
	using std::swap;
	swap(texture_1.rendererID, texture_2.rendererID);
	swap(texture_1.width, texture_2.width);
	swap(texture_1.height, texture_2.height);
	swap(texture_1.BPP, texture_2.BPP);
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
