#pragma once
#include <glad/glad.h>
#include <utility>

class IndexBuffer
{
  public:
	unsigned int rendererID;
	unsigned int count;
	IndexBuffer() = default;
	IndexBuffer(const void *data, unsigned int count);
	IndexBuffer(const IndexBuffer &indexBuffer);
	IndexBuffer(IndexBuffer &&indexBuffer) noexcept;
	IndexBuffer &operator=(IndexBuffer indexBuffer);
	~IndexBuffer();
	friend void swap(IndexBuffer &indexBuffer_1, IndexBuffer &indexBuffer_2);
	void Bind() const;
	void Unbind() const;
};