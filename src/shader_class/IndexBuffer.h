#pragma once
#include <glad/glad.h>

class IndexBuffer
{
public:
	unsigned int rendererID;
	unsigned int count;
	IndexBuffer(const void *data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
};