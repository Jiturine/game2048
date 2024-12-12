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
	// 文字投影矩阵设置
	Text::Init(screenWidth, screenHeight);
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