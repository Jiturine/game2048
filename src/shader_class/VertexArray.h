#pragma once
#include <glad/glad.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexBuffer;
class VertexBufferLayout;

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