#include <iostream>
#include "List.h"
#include "Renderer.h"
#include "ScoreManager.h"
#include "Game.h"
#include "OpenGL.h"
#include "Text.h"
#include "Log.h"

constexpr unsigned int SCREEN_WIDTH = 1920;
constexpr unsigned int SCREEN_HEIGHT = 1080;
const char *SCREEN_NAME = "game2048";

int main()
{
	Log::Init();
#if 0 
	List<int> list;
	ScoreManager::rankList.Add(ScoreManager::ScoreInfo(4, "name1"),
							   ScoreManager::ScoreInfo(2, "name2"),
							   ScoreManager::ScoreInfo(5, "name3"),
							   ScoreManager::ScoreInfo(1, "name4"));
	ScoreManager::rankList.Sort();
	for (auto scoreInfo : ScoreManager::rankList)
	{
		std::cout << scoreInfo.userName << " ";
	}
	std::cout << std::endl;
#endif
#if 1
	OpenGL::Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);

	// float vertices[] = {
	// 	-0.5f, 0.5f,  // 左上顶点
	// 	0.5f, 0.5f,	  // 右上顶点
	// 	-0.5f, -0.5f, // 左下顶点
	// 	0.5f, -0.5f	  // 右下顶点
	// };
	// unsigned int indices[] = {
	// 	0, 1, 2, // 左上三角形
	// 	1, 2, 3	 // 右下三角形
	// };
	// VertexArray vertexArray;
	// vertexArray.Bind();
	// VertexBuffer vertexBuffer(vertices, 4 * 2 * sizeof(float));
	// VertexBufferLayout layout;
	// layout.Push<float>(2);
	// vertexArray.AddBuffer(vertexBuffer, layout);
	// IndexBuffer indexBuffer(indices, 3 * 2);

	Shader shader("shaders/text_shader/text_vertex_shader.vs",
				  "shaders/text_shader/text_fragment_shader.fs");
	// Renderer renderer;
	Text::LoadFont("HarmonyOS_Sans_SC_Regular.ttf", 48);

	while (!OpenGL::ShouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Text::Render(shader, "Score:", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		OpenGL::Update();
	}
	OpenGL::Terminate();
#endif
#if 0
	Game::Init();
	while (!Game::gameOver)
	{
		Game::Print();
		Game::Update();
	}
#endif
	return 0;
}