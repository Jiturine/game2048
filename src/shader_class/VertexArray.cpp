#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &rendererID);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}
void VertexArray::Bind() const
{
	glBindVertexArray(rendererID);
}
void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
void VertexArray::AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout)
{
	Bind();
	vertexBuffer.Bind();
	unsigned long long offset = 0;
	for (unsigned int i = 0; i < layout.elements.size(); i++)
	{
		const auto &element = layout.elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.stride, (const void *)offset);
		offset += element.count * element.SizeOfType();
	}
}