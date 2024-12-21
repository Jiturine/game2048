#pragma once

#include <conio.h>
#include <random>
#include <iostream>
#include <iomanip>
#include "OpenGL.h"
#include "GameState.h"

class Game
{
  public:
	Game() = delete;
	static constexpr int SIZE = 5;
	static void Init();
	static void Update();
	static void Print();
	static int grid[SIZE][SIZE][SIZE];
	static int score;
	static bool gameOver;
	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static std::unique_ptr<GameState> currentState;
	template <class T>
	static void SwitchState();

  private:
	static void RevolveX();
	static void RevolveY();
	static void Compress();
	static char inputKey;
};

#include "Game.tpp"