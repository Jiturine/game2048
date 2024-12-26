#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &rendererID);
}
VertexArray::VertexArray(const VertexArray &vertexArray)
{
	glGenVertexArrays(1, &rendererID);
	glBindBuffer(GL_COPY_READ_BUFFER, vertexArray.rendererID);
	glBindBuffer(GL_COPY_WRITE_BUFFER, rendererID);
	vertexArray.Bind();
	int bufferSize;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
}
VertexArray::VertexArray(VertexArray &&vertexArray) noexcept
	: VertexArray()
{
	swap(vertexArray, *this);
}
VertexArray &VertexArray::operator=(VertexArray vertexArray)
{
	swap(vertexArray, *this);
	return *this;
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}
void swap(VertexArray &vertexArray_1, VertexArray &vertexArray_2)
{
	using std::swap;
	swap(vertexArray_1.rendererID, vertexArray_2.rendererID);
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