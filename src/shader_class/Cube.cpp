#include "Cube.h"

void Cube::Init()
{
	// 生成VBO，VAO
	vertexArray = std::make_unique<VertexArray>();
	vertexArray->Bind();
	float vertices[] = {
		// 上面
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // 上左后 0 --------- 0
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,	// 上左前 1 --------- 1
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	// 上右前 2 --------- 2
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	// 上右后 3 --------- 3
		// 前面
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,	// 上左前 1 --------- 4
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // 下左前 5 --------- 5
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	// 下右前 6 --------- 6
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,	// 上右前 2 --------- 7
		// 左面
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,	 // 上左后 0 --------- 8
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 下左后 4 --------- 9
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	 // 下左前 5 --------- 10
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,	 // 上左前 1 --------- 11
		// 右面
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f,	// 上右前 2 --------- 12
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,	// 下右前 6 --------- 13
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 下右后 7 --------- 14
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	// 上右后 3 --------- 15
		// 后面
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f,	 // 上右后 3 --------- 16
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f,	 // 下右后 7 --------- 17
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 下左后 4 --------- 18
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,	 // 上左后 0 --------- 19
		// 底面
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 下左后 4 --------- 20
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,	 // 下左前 5 --------- 21
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f,	 // 下右前 6 --------- 22
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f	 // 下右后 7 --------- 23
	};
	unsigned int faceIndices[] = {
		0, 1, 2,	//
		2, 3, 0,	//
		4, 5, 6,	//
		6, 7, 4,	//
		8, 9, 10,	//
		10, 11, 8,	//
		12, 13, 14, //
		14, 15, 12, //
		16, 17, 18, //
		18, 19, 16, //
		20, 21, 22, //
		22, 23, 20	//
	};
	unsigned int lineIndices[] =
		{0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 6, 7, 16, 17, 18, 19, 20, 21, 21, 22, 22, 23, 23, 20};
	vertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	vertexArray->AddBuffer(*vertexBuffer, layout);
	faceIndexBuffer = std::make_unique<IndexBuffer>(faceIndices, 3 * 12);
	lineIndexBuffer = std::make_unique<IndexBuffer>(lineIndices, 2 * 12);
	// 编译着色器
	shader = std::make_unique<Shader>("shaders/cube_shader/cube_vertex_shader.vs",
									  "shaders/cube_shader/cube_fragment_shader.fs");
	// 加载纹理
	textures[0] = new Texture("resources/textures/0.png");
	for (int i = 1; i <= 13; i++)
	{
		textures[i] = new Texture(std::format("resources/textures/{}.png", 1 << i));
	}
}
void Cube::Render(float x, float y, float z, float scale, int num)
{
	shader->Bind();
	glm::mat4 model = OpenGL::rotationMatrix;
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	glm::mat4 view = glm::lookAt(
		OpenGL::cameraPosition,		 // 相机位置（稍微在立方体前方）
		glm::vec3(0.0f, 0.0f, 0.0f), // 目标点（看向场景原点）
		glm::vec3(0.0f, 1.0f, 0.0f)	 // 上方向（Y轴向上）
	);
	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),
		(float)OpenGL::screenWidth / (float)OpenGL::screenHeight,
		0.1f, 100.0f);
	auto mvp = projection * view * model;
	size_t index = ((num == 0) ? 0 : log2(num));
	textures[index]->Bind();
	shader->SetUniform("mvp", mvp);
	shader->SetUniform("uTexture", 0);
	shader->SetUniform("uColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Renderer::Draw(*vertexArray, *faceIndexBuffer, *shader);
	shader->SetUniform("uColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	Renderer::Draw(*vertexArray, *lineIndexBuffer, *shader, Renderer::DrawMode::Lines);
}

std::unique_ptr<VertexArray> Cube::vertexArray;
std::unique_ptr<VertexBuffer> Cube::vertexBuffer;
std::unique_ptr<IndexBuffer> Cube::faceIndexBuffer;
std::unique_ptr<IndexBuffer> Cube::lineIndexBuffer;
std::unique_ptr<Shader> Cube::shader;
Texture *Cube::textures[14];
glm::mat4 Cube::transform;
