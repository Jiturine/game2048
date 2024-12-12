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
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	void ChangeData(const void *data, unsigned int size) const;
};