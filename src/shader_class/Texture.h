#pragma once
#include <stb_image.h>
#include <glad/glad.h>
#include <string>
#include <filesystem>
#include "SysConfig.h"
#include "Log.h"

class Texture
{
  public:
	Texture() = default;
	Texture(const std::string &path);
	Texture(const Texture &texture);
	Texture(Texture &&texture) noexcept;
	Texture &operator=(Texture texture);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	friend void swap(Texture &texture_1, Texture texture_2);

	unsigned int rendererID;
	int width;
	int height;
	int BPP;
};