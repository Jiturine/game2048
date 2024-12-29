#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Renderer.h"
#include "Texture.h"

class VertexArray;
class VertexBuffer;

class Cube
{
  public:
	Cube() = delete;
	static void Init();
	static void Render(float x, float y, float z, float scale, int num);

  private:
	static std::unique_ptr<VertexArray> vertexArray;
	static std::unique_ptr<VertexBuffer> vertexBuffer;
	static std::unique_ptr<IndexBuffer> faceIndexBuffer;
	static std::unique_ptr<IndexBuffer> lineIndexBuffer;
	static std::unique_ptr<Shader> shader;
	static glm::mat4 transform;
	static Texture *textures[];
};
