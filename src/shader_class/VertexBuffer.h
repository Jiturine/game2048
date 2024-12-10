#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
	unsigned int rendererID;
	VertexBuffer(const void *data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
};