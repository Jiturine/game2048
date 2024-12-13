#pragma once

#include <glad/glad.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class VertexArray;

class Renderer
{
  public:
	static void Draw(const VertexArray &vertexArray, const IndexBuffer &inderBuffer, const Shader &shader);
};