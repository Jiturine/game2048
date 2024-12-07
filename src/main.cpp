#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int main()
{
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game2048", NULL, NULL);
	glfwMakeContextCurrent(window);
	// 一定要在设置上下文之后再初始化glad!!!
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
	std::cout << glGetString(GL_VERSION) << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		// render here
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
