#pragma once

#include <glad/glad.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class VertexArray;

class Renderer
{
  public:
	enum class DrawMode
	{
		Triangles,
		Lines
	};
	static void Draw(const VertexArray &vertexArray, const IndexBuffer &inderBuffer, const Shader &shader, DrawMode drawMode = DrawMode::Triangles);
};