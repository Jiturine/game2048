#include <iostream>
#include "List.h"
#include "Renderer.h"
#include "ScoreManager.h"
#include "Game3D.h"
#include "OpenGL.h"
#include "Text.h"
#include "Log.h"
#include "Cube.h"

constexpr unsigned int SCREEN_WIDTH = 1920;
constexpr unsigned int SCREEN_HEIGHT = 1080;
const char *SCREEN_NAME = "game2048";
std::map<int, glm::vec4> color = {
	{0, glm::vec4(0.95f, 0.95f, 0.95f, 1.0f)},
	{2, glm::vec4(0.9f, 0.9f, 0.9f, 1.0f)},
	{4, glm::vec4(0.85f, 0.85f, 0.85f, 1.0f)},
	{8, glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)},
	{16, glm::vec4(0.75f, 0.75f, 0.75f, 1.0f)},
	{32, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)},
	{64, glm::vec4(0.65f, 0.65f, 0.65f, 1.0f)},
	{128, glm::vec4(0.6f, 0.6f, 0.6f, 1.0f)},
	{256, glm::vec4(0.55f, 0.55f, 0.55f, 1.0f)},
	{512, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)},
	{1024, glm::vec4(0.45f, 0.45f, 0.45f, 1.0f)},
	{2048, glm::vec4(0.4f, 0.4f, 0.4f, 1.0f)},
};

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
	Shader textShader("shaders/text_shader/text_vertex_shader.vs",
					  "shaders/text_shader/text_fragment_shader.fs");
	// Renderer renderer;
	Text::LoadFont("HarmonyOS_Sans_SC_Regular.ttf", 48);

	// 编译着色器
	auto shader = new Shader("shaders/rectangle_shader/rectangle_vertex_shader.vs",
							 "shaders/rectangle_shader/rectangle_fragment_shader.fs");
	Game3D::Init();
	while (!OpenGL::ShouldClose() && !Game::gameOver)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		// Text::Render(textShader, "Score:" + std::to_string(Game::score), 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		// for (int i = 1; i <= 4; i++)
		// 	for (int j = 1; j <= 4; j++)
		// 	{
		// 		Rectangle::Render(460.0f + j * 200.0f, 40.0f + (5 - i) * 200.0f, 190.0f, 190.0f, color[Game::grid[i][j]]);
		// 		if (Game::grid[i][j])
		// 		{
		// 			Text::Render(textShader, std::to_string(Game::grid[i][j]), 460.0f + j * 200.0f, 40.0f + (5 - i) * 200.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		// 		}
		// 	}
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				for (int k = 1; k <= 4; k++)
					Cube::Render(-2.5f + 1.01f * i, -2.5f + 1.01f * j, -2.5f + 1.01f * k, 0.0f, color[Game3D::grid[i][j][k]]);
		Game3D::Print();
		// Game3D::Update();

		OpenGL::Update();
	}
	OpenGL::Terminate();
#endif
	return 0;
}