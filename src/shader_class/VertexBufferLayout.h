#pragma once
#include <glad/glad.h>
#include <vector>

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	template <typename T>
	void Push(unsigned int count);

	class VertexBufferElement
	{
	public:
		VertexBufferElement(unsigned int type, unsigned int count, bool normalized);
		unsigned int type;
		unsigned int count;
		bool normalized;
		unsigned int SizeOfType() const;
	};

	std::vector<VertexBufferElement> elements;
	unsigned int stride;
};