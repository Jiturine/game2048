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
	struct Grid
	{
		int num;
		int preNum;
		struct Index
		{
			int x, y, z;
		} indexOfNum, indexOfMergedNum, targetIndex;
	};
	static Grid grid[SIZE][SIZE][SIZE];
	static int score;
	static bool gameOver;
	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static std::unique_ptr<GameState> currentState;
	template <class T>
	static void SwitchState();
	static float easing(float t)
	{
		return t * t * (3.0f - 2.0f * t);
	}
	static float elapsedTime;
	static constexpr float totalTime = 0.1f;
	static bool numChanged;

  private:
	static void
	RevolveX();
	static void RevolveY();
	static void Compress();
	static char GetTargetFace();
	static char inputKey;
};

#include "Game.tpp"