#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Renderer.h"
#include "Texture.h"
#include "Log.h"

class VertexArray;
class VertexBuffer;

class Cube
{
  public:
	static void Init();
	static void Render(float x, float y, float z, float scale, int num);

  private:
	static VertexArray *vertexArray;
	static VertexBuffer *vertexBuffer;
	static IndexBuffer *faceIndexBuffer;
	static IndexBuffer *lineIndexBuffer;
	static Shader *shader;
	static glm::mat4 transform;
	static Texture *textures[];
};
