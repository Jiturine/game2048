#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Renderer.h"
#include "Log.h"

class VertexArray;
class VertexBuffer;

class Rectangle
{
  public:
	static void Init(unsigned int screenWidth, unsigned int screenHeight);
	static void Render(float x, float y, float width, float height, glm::vec4 color);

  private:
	static VertexArray *vertexArray;
	static VertexBuffer *vertexBuffer;
	static IndexBuffer *indexBuffer;
	static Shader *shader;
	static glm::mat4 transform;
	static glm::mat4 projection;
};
