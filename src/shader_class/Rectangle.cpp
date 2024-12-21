#include "Rectangle.h"

void Rectangle::Init(unsigned int screenWidth, unsigned int screenHeight)
{
	Rectangle::projection = glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight));
	// 生成VBO，VAO
	vertexArray = new VertexArray;
	vertexArray->Bind();
	float vertices[] = {
		0.5f, 0.5f,	  //
		-0.5f, 0.5f,  //
		-0.5f, -0.5f, //
		0.5f, -0.5f	  //
	};
	vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	vertexArray->AddBuffer(*vertexBuffer, layout);
	unsigned int indices[] = {0, 1, 2, 0, 2, 3};
	indexBuffer = new IndexBuffer(indices, 6);
	// 编译着色器
	shader = new Shader("shaders/rectangle_shader/rectangle_vertex_shader.vs",
						"shaders/rectangle_shader/rectangle_fragment_shader.fs");
}
void Rectangle::Render(float x, float y, float width, float height, glm::vec4 color)
{
	shader->Bind();
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	transform = glm::scale(transform, glm::vec3(width, height, 1.0f));
	auto mvp = projection * transform;
	shader->SetUniform("mvp", mvp);
	shader->SetUniform("uColor", color);
	Renderer::Draw(*vertexArray, *indexBuffer, *shader);
}

VertexArray *Rectangle::vertexArray;
VertexBuffer *Rectangle::vertexBuffer;
Shader *Rectangle::shader;
IndexBuffer *Rectangle::indexBuffer;
glm::mat4 Rectangle::projection;
glm::mat4 Rectangle::transform;