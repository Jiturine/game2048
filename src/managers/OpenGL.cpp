#include "OpenGL.h"

unsigned int OpenGL::screenWidth;
unsigned int OpenGL::screenHeight;
std::string OpenGL::windowName;
GLFWwindow *OpenGL::window;

void OpenGL::Init(const unsigned int &screenWidth, const unsigned int &screenHeight, const std::string &windowName)
{
	OpenGL::screenWidth = screenWidth;
	OpenGL::screenHeight = screenHeight;
	OpenGL::windowName = windowName;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window = glfwCreateWindow(screenWidth, screenHeight, windowName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
	glViewport(0, 0, screenWidth, screenHeight);
	// 启用表面剔除
	glEnable(GL_CULL_FACE);
	// 启用混合
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 取消粘滞键
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
	glfwSetKeyCallback(window, Game::KeyCallback);
	// 文字投影矩阵设置
	Text::Init(screenWidth, screenHeight);
	Rectangle::Init(screenWidth, screenHeight);
}

void OpenGL::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool OpenGL::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void OpenGL::Terminate()
{
	glfwTerminate();
}

bool OpenGL::GetKeyDown(char key)
{
	if (key == 'w')
		return glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	if (key == 's')
		return glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
	if (key == 'a')
		return glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	if (key == 'd')
		return glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	return false;
}