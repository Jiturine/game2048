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
				{
					Cube::Render(-2.5f + 1.01f * i, -2.5f + 1.01f * j, -2.5f + 1.01f * k, 1.0f, 0);
					if (Game::elapsedTime < Game::totalTime)
					{
						if (Game::grid[i][j][k].preNum != 0)
						{
							int tx = Game::grid[i][j][k].targetIndex.x;
							int ty = Game::grid[i][j][k].targetIndex.y;
							int tz = Game::grid[i][j][k].targetIndex.z;
							float t = Game::elapsedTime / Game::totalTime;
							float offsetX = float(tx - i) * Game::easing(t);
							float offsetY = float(ty - j) * Game::easing(t);
							float offsetZ = float(tz - k) * Game::easing(t);
							Cube::Render(-2.5f + 1.01f * ((float)i + offsetX), -2.5f + 1.01f * ((float)j + offsetY), -2.5f + 1.01f * ((float)k + offsetZ), 1.001f, Game::grid[i][j][k].preNum);
						}
					}
					else
					{
						if (Game::grid[i][j][k].num != 0)
						{
							Cube::Render(-2.5f + 1.01f * i, -2.5f + 1.01f * j, -2.5f + 1.01f * k, 1.001f, Game::grid[i][j][k].num);
						}
					}
				}

		Game::Update();
		OpenGL::Update();
	}
	OpenGL::Terminate();
	return 0;
}