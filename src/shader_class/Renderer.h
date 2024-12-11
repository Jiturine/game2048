#pragma once
#include <glad/glad.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class Renderer
{
  public:
	void Draw(const VertexArray &vertexArray, const IndexBuffer &inderBuffer, const Shader &shader) const;
};