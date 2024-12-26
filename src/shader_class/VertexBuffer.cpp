#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size, DataMode dataMode)
{
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	switch (dataMode)
	{
	case DataMode::STATIC:
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		break;
	case DataMode::DYNAMIC:
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		break;
	case DataMode::STREAM:
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
		break;
	}
}
VertexBuffer::VertexBuffer(const VertexBuffer &vertexBuffer)
{
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_COPY_READ_BUFFER, vertexBuffer.rendererID);
	int bufferSize;
	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	glBindBuffer(GL_COPY_WRITE_BUFFER, rendererID);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
}
VertexBuffer::VertexBuffer(VertexBuffer &&vertexBuffer) noexcept
	: VertexBuffer()
{
	swap(vertexBuffer, *this);
}
VertexBuffer &VertexBuffer::operator=(VertexBuffer &vertexBuffer)
{
	swap(vertexBuffer, *this);
	return *this;
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void swap(VertexBuffer vertexBuffer_1, VertexBuffer vertexBuffer_2)
{
	using std::swap;
	swap(vertexBuffer_1.rendererID, vertexBuffer_2.rendererID);
}
void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}
void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::ChangeData(const void *data, unsigned int size) const
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}