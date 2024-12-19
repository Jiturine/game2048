#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Text.h"
#include "Rectangle.h"
#include "Cube.h"
#include "Game.h"

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
	static bool GetKeyDown(char key);
	static void MouseCallBack(GLFWwindow *window, double xpos, double ypos);
	static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
	static float yaw;
	static float pitch;
	static glm::vec3 cameraPosition;

  private:
	static GLFWwindow *window;
	static bool mouseDragging;
	static double lastX;
	static double lastY;
	OpenGL() = delete;
};