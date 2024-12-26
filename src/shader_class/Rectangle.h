#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Renderer.h"
#include "Log.h"
#include <memory>

class VertexArray;
class VertexBuffer;

class Rectangle
{
  public:
	Rectangle() = delete;
	static void Init(unsigned int screenWidth, unsigned int screenHeight);
	static void Render(float x, float y, float width, float height, glm::vec4 color);

  private:
	static std::unique_ptr<VertexArray> vertexArray;
	static std::unique_ptr<VertexBuffer> vertexBuffer;
	static std::unique_ptr<IndexBuffer> indexBuffer;
	static std::unique_ptr<Shader> shader;
	static glm::mat4 transform;
	static glm::mat4 projection;
};
