#include "Cube.h"

void Cube::Init()
{
	// 生成VBO，VAO
	vertexArray = new VertexArray;
	vertexArray->Bind();
	float vertices[] = {
		-0.5f, 0.5f, -0.5f,	 // 上左后 0
		-0.5f, 0.5f, 0.5f,	 // 上左前 1
		0.5f, 0.5f, 0.5f,	 // 上右前 2
		0.5f, 0.5f, -0.5f,	 // 上右后 3
		-0.5f, -0.5f, -0.5f, // 下左后 4
		-0.5f, -0.5f, 0.5f,	 // 下左前 5
		0.5f, -0.5f, 0.5f,	 // 下右前 6
		0.5f, -0.5f, -0.5f	 // 下右后 7
	};
	unsigned int faceIndices[] = {
		0, 1, 2, //
		2, 3, 0, //
		1, 5, 2, //
		5, 6, 2, //
		2, 6, 7, //
		7, 3, 2, //
		3, 7, 4, //
		4, 0, 3, //
		0, 4, 5, //
		5, 1, 0, //
		5, 6, 4, //
		6, 7, 4};
	unsigned int lineIndices[] = {
		0, 1, 1, 2, 2, 3, 0, 3, 1, 5, 2, 6, 3, 7, 0, 4, 4, 5, 5, 6, 6, 7, 7, 4};
	vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	vertexArray->AddBuffer(*vertexBuffer, layout);
	faceIndexBuffer = new IndexBuffer(faceIndices, 3 * 12);
	lineIndexBuffer = new IndexBuffer(lineIndices, 4 * 6);
	// 编译着色器
	shader = new Shader("shaders/cube_shader/cube_vertex_shader.vs",
						"shaders/cube_shader/cube_fragment_shader.fs");
}
void Cube::Render(float x, float y, float z, float length, glm::vec4 color)
{
	shader->Bind();
	glm::mat4 model = glm::mat4(1.0f);
	model = OpenGL::rotationMatrix * model;
	model = glm::translate(model, glm::vec3(x, y, z));
	glm::mat4 view = glm::lookAt(
		OpenGL::cameraPosition,		 // 相机位置（稍微在立方体前方）
		glm::vec3(0.0f, 0.0f, 0.0f), // 目标点（看向场景原点）
		glm::vec3(0.0f, 1.0f, 0.0f)	 // 上方向（Y轴向上）
	);
	auto projection = glm::perspective(glm::radians(45.0f), (float)OpenGL::screenWidth / (float)OpenGL::screenHeight, 0.1f, 100.0f);
	// auto projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	auto mvp = projection * view * model;

	shader->SetUniform("mvp", mvp);
	shader->SetUniform("uColor", color);
	Renderer::Draw(*vertexArray, *faceIndexBuffer, *shader);
	shader->SetUniform("uColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	Renderer::Draw(*vertexArray, *lineIndexBuffer, *shader, Renderer::DrawMode::Lines);
}

VertexArray *Cube::vertexArray;
VertexBuffer *Cube::vertexBuffer;
Shader *Cube::shader;
IndexBuffer *Cube::faceIndexBuffer;
IndexBuffer *Cube::lineIndexBuffer;
glm::mat4 Cube::transform;
