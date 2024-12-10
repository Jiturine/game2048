#include "Renderer.h"

void Renderer::Draw(const VertexArray &vertexArray, const IndexBuffer &inderBuffer, const Shader &shader) const
{
	vertexArray.Bind();
	inderBuffer.Bind();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, inderBuffer.count, GL_UNSIGNED_INT, nullptr);
}