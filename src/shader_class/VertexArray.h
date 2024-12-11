#pragma once
#include <glad/glad.h>
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray
{
  public:
	unsigned int rendererID;
	VertexArray();
	~VertexArray();
	void Bind() const;
	void Unbind() const;
	void AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout);
};