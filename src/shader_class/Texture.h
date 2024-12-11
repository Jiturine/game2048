#pragma once
#include <glad/glad.h>
#include "Image.h"
#include <string>
#include "SysConfig.h"

class Texture
{
  public:
	unsigned int rendererID;
	Texture(const std::string &path);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	int width;
	int height;
	int BPP;
	unsigned char *localBuffer;
	std::string filePath;
};