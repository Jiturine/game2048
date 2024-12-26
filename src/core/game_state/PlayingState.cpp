#include "PlayingState.h"

void PlayingState::Render()
{
	Text::Render(std::format("Score:{}", Game::score), 25.0f, 25.0f, 1.2f, glm::vec3(0.0f, 0.0f, 0.0f));
	Text::Render(std::format("Record:{}",
							 (Game::score > ScoreManager::GetHighestScore()) ? Game::score : ScoreManager::GetHighestScore()),
				 25.0f, 100.0f, 1.2f, glm::vec3(0.0f, 0.0f, 0.0f));
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
						Cube::Render(-2.5f + 1.01f * ((float)i + offsetX), -2.5f + 1.01f * ((float)j + offsetY), -2.5f + 1.01f * ((float)k + offsetZ), 1.005f, Game::grid[i][j][k].preNum);
					}
				}
				else
				{
					if (Game::grid[i][j][k].num != 0)
					{
						Cube::Render(-2.5f + 1.01f * i, -2.5f + 1.01f * j, -2.5f + 1.01f * k, 1.005f, Game::grid[i][j][k].num);
					}
				}
			}
}

void PlayingState::Update()
{
	Game::Update();
}