#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void *data, unsigned int count)
	: count(count)
{
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}
IndexBuffer::IndexBuffer(const IndexBuffer &indexBuffer)
{
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.rendererID);
	int bufferSize = 0;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_COPY_READ_BUFFER, indexBuffer.rendererID);
	glBindBuffer(GL_COPY_WRITE_BUFFER, rendererID);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
}
IndexBuffer::IndexBuffer(IndexBuffer &&indexBuffer) noexcept
{
	swap(indexBuffer, *this);
}
IndexBuffer &IndexBuffer::operator=(IndexBuffer indexBuffer)
{
	swap(indexBuffer, *this);
	return *this;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}
void swap(IndexBuffer &indexBuffer_1, IndexBuffer &indexBuffer_2)
{
	using std::swap;
	swap(indexBuffer_1.rendererID, indexBuffer_2.rendererID);
	swap(indexBuffer_1.count, indexBuffer_2.count);
}
void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}
void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}