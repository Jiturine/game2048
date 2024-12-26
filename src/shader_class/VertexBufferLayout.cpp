#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferElement::VertexBufferElement(unsigned int type, unsigned int count, bool normalized)
	: type(type), count(count), normalized(normalized) {}
unsigned int VertexBufferLayout::VertexBufferElement::SizeOfType() const
{
	switch (type)
	{
	case GL_FLOAT:
		return sizeof(float);
	case GL_UNSIGNED_INT:
		return sizeof(unsigned int);
	case GL_UNSIGNED_BYTE:
		return sizeof(unsigned char);
	}
	return 0;
}
template <>
void VertexBufferLayout::Push<float>(unsigned int count)
{
	elements.emplace_back(GL_FLOAT, count, false);
	stride += count * sizeof(float);
}
template <>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
	elements.emplace_back(GL_UNSIGNED_INT, count, false);
	stride += count * sizeof(unsigned int);
}
template <>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
	elements.emplace_back(GL_UNSIGNED_BYTE, count, false);
	stride += count * sizeof(unsigned char);
}