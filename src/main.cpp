#include <iostream>
#include "List.h"
#include "Renderer.h"
#include "ScoreManager.h"
#include "Game.h"
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
	OpenGL::Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);
	Game::Init();

	while (!OpenGL::ShouldClose() && !Game::gameOver)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		Text::Render(std::format("Score:{}", Game::score), 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				for (int k = 1; k <= 4; k++)
					Cube::Render(-2.5f + 1.01f * j, -2.5f + 1.01f * k, -2.5f + 1.01f * i, Game::grid[i][j][k]);
		Game::Update();
		OpenGL::Update();
	}
	OpenGL::Terminate();
	return 0;
}