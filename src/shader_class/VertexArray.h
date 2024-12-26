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
	VertexArray(const VertexArray &vertexArray);
	VertexArray(VertexArray &&vertexArray) noexcept;
	VertexArray &operator=(VertexArray vertexArray);
	~VertexArray();
	friend void swap(VertexArray &vertexArray_1, VertexArray &vertexArray_2);
	void Bind() const;
	void Unbind() const;
	void AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout);
};