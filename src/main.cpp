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
	Text::LoadFont("HarmonyOS_Sans_SC_Regular.ttf", 48);

	Game3D::Init();
	while (!OpenGL::ShouldClose() && !Game3D::gameOver)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		Text::Render(textShader, "Score:" + std::to_string(Game3D::score), 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				for (int k = 1; k <= 4; k++)
					Cube::Render(-2.5f + 1.01f * j, -2.5f + 1.01f * k, -2.5f + 1.01f * i, Game3D::grid[i][j][k]);
		Game3D::Update();
		OpenGL::Update();
	}
	OpenGL::Terminate();
#endif
	return 0;
}