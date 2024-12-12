#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Text.h"

class OpenGL
{
  public:
	static unsigned int screenWidth;
	static unsigned int screenHeight;
	static std::string windowName;
	static void Init(const unsigned int &screenWidth, const unsigned int &screenHeight, const std::string &windowName);
	static void Update();
	static bool ShouldClose();
	static void Terminate();

  private:
	static GLFWwindow *window;
	OpenGL() = delete;
};