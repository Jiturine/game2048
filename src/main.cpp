#include <iostream>
#include "List.h"
#include "Renderer.h"
#include "ScoreManager.h"
#include "Game.h"
#include "OpenGL.h"
#include "Text.h"
#include "Cube.h"

constexpr unsigned int SCREEN_WIDTH = 1920;
constexpr unsigned int SCREEN_HEIGHT = 1080;
const char *SCREEN_NAME = "game2048";

int main()
{
	Log::Init();
	OpenGL::Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);
	Game::Init();
	Game::SwitchState<StartState>();
	ScoreManager::Init();
	while (!OpenGL::ShouldClose())
	{
		OpenGL::Render();
		Game::currentState->Update();
		OpenGL::Update();
	}
	if (!Game::gameOver && Game::score != 0)
	{
		ScoreManager::AddScore(Game::score);
	}
	OpenGL::Terminate();
	return 0;
}