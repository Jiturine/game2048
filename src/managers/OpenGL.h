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
	OpenGL() = delete;
	static unsigned int screenWidth;
	static unsigned int screenHeight;
	static std::string windowName;
	static void Init(const unsigned int &screenWidth, const unsigned int &screenHeight, const std::string &windowName);
	static void Update();
	static bool ShouldClose();
	static void Terminate();
	static void MouseCallBack(GLFWwindow *window, double xpos, double ypos);
	static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
	static glm::vec3 cameraPosition;
	static glm::mat4 rotationMatrix;
	static float deltaTime;

  private:
	static constexpr float sensitivity = 0.05f; // 控制转动灵敏度
	static float lastTime;
	static GLFWwindow *window;
	static bool mouseDragging;
	static bool mouseEnter;
	static double lastX;
	static double lastY;
	static float xoffset;
	static float yoffset;
};