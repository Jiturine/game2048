#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "List.h"
#include "ScoreManager.h"
#include "Renderer.h"

constexpr unsigned int SCREEN_WIDTH = 1920;
constexpr unsigned int SCREEN_HEIGHT = 1080;
const char *SCREEN_NAME = "game2048";

int main()
{
	List<int> list;
	ScoreManager::rankList.Add(ScoreManager::ScoreInfo(4, "name1"),
							   ScoreManager::ScoreInfo(2, "name2"),
							   ScoreManager::ScoreInfo(5, "name3"),
							   ScoreManager::ScoreInfo(1, "name4"));
	ScoreManager::rankList.Sort();
	for (auto scoreInfo : ScoreManager::rankList)
	{
		std::cout << scoreInfo.userName << " ";
	}
	std::cout << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME, NULL, NULL);
	glfwMakeContextCurrent(window);
	// 一定要在设置上下文之后再初始化glad!!!
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
	std::cout << glGetString(GL_VERSION) << std::endl;

	float vertices[] = {
		-0.5f, 0.5f,  // 左上顶点
		0.5f, 0.5f,	  // 右上顶点
		-0.5f, -0.5f, // 左下顶点
		0.5f, -0.5f	  // 右下顶点
	};
	unsigned int indices[] = {
		0, 1, 2, // 左上三角形
		1, 2, 3	 // 右下三角形
	};
	VertexArray vertexArray;
	vertexArray.Bind();
	VertexBuffer vertexBuffer(vertices, 4 * 2 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	vertexArray.AddBuffer(vertexBuffer, layout);
	IndexBuffer indexBuffer(indices, 3 * 2);

	Shader shader("shaders/simple_shader/simple_vertex_shader.vs",
				  "shaders/simple_shader/simple_fragment_shader.fs");
	shader.Bind();
	Renderer renderer;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		// ----------------- render here
		renderer.Draw(vertexArray, indexBuffer, shader);
		// -----------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}