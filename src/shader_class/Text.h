#pragma once

#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "SysConfig.h"

class VertexArray;
class VertexBuffer;

class Text
{
  public:
	Text() = delete;
	static void Init(unsigned int screenWidth, unsigned int screenHeight);
	static void LoadFont(const std::string &fontName, int fontHeight);
	static void Render(const std::string &text, float x, float y, float scale, glm::vec3 color);
	class Character
	{
	  public:
		unsigned int textureID; // 字形纹理的ID
		glm::ivec2 size;		// 字形大小
		glm::ivec2 bearing;		// 从基准线到字形左部/顶部的偏移值
		unsigned int advance;	// 原点距下一个字形原点的距离
	};
	static std::map<char, Character> Characters;
	static glm::mat4 projection;

  private:
	static std::unique_ptr<VertexArray> vertexArray;
	static std::unique_ptr<VertexBuffer> vertexBuffer;
	static std::unique_ptr<Shader> shader;
};