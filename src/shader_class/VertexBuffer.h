#pragma once
#include <glad/glad.h>
#include "OpenGL.h"

class OpenGL;

class VertexBuffer
{
  public:
	enum class DataMode
	{
		STATIC,
		DYNAMIC,
		STREAM
	};
	unsigned int rendererID;
	VertexBuffer() = default;
	VertexBuffer(const void *data, unsigned int size, DataMode dataMode = DataMode::STATIC);
	VertexBuffer(const VertexBuffer &vertexBuffer);
	VertexBuffer(VertexBuffer &&vertexBuffer) noexcept;
	VertexBuffer &operator=(VertexBuffer &vertexBuffer);
	~VertexBuffer();
	friend void swap(VertexBuffer vertexBuffer_1, VertexBuffer vertexBuffer_2);
	void Bind() const;
	void Unbind() const;
	void ChangeData(const void *data, unsigned int size) const;
};