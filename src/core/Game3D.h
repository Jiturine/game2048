#pragma once

#include <conio.h>
#include <random>
#include <iostream>
#include <iomanip>
#include "OpenGL.h"

class Game3D
{
  public:
	static constexpr int SIZE = 5;
	static void Init();
	static void Update();
	static void Print();
	static int grid[SIZE][SIZE][SIZE];
	static int score;
	static bool gameOver;
	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

  private:
	Game3D() = delete;
	static void RevolveX();
	static void RevolveY();
	static void Compress();
	static char inputKey;
};