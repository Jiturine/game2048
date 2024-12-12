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
VertexBuffer ::~VertexBuffer()
{
	glDeleteBuffers(1, &rendererID);
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