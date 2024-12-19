#include "Renderer.h"

void Renderer::Draw(const VertexArray &vertexArray, const IndexBuffer &inderBuffer, const Shader &shader, Renderer::DrawMode drawMode)
{
	vertexArray.Bind();
	inderBuffer.Bind();
	shader.Bind();
	switch (drawMode)
	{
	case DrawMode::Triangles:
		glDrawElements(GL_TRIANGLES, inderBuffer.count, GL_UNSIGNED_INT, nullptr);
		break;
	case DrawMode::Lines:
		glDrawElements(GL_LINES, inderBuffer.count, GL_UNSIGNED_INT, nullptr);
		break;
	}
}