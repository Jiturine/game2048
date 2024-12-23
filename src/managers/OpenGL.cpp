#include "OpenGL.h"

unsigned int OpenGL::screenWidth;
unsigned int OpenGL::screenHeight;
std::string OpenGL::windowName;
GLFWwindow *OpenGL::window;
double OpenGL::lastX;
double OpenGL::lastY;
float OpenGL::xoffset = 0.0f;
float OpenGL::yoffset = 0.0f;
float OpenGL::lastTime;
float OpenGL::deltaTime;
bool OpenGL::mouseDragging;
bool OpenGL::mouseEnter;
glm::vec3 OpenGL::cameraPosition;
glm::mat4 OpenGL::rotationMatrix = glm::mat4(1.0f);

void OpenGL::Init(const unsigned int &screenWidth, const unsigned int &screenHeight, const std::string &windowName)
{
	OpenGL::screenWidth = screenWidth;
	OpenGL::screenHeight = screenHeight;
	OpenGL::windowName = windowName;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 全屏
	// GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	// const GLFWvidmode *mode = glfwGetVideoMode(monitor);
	// window = glfwCreateWindow(mode->width, mode->height, windowName.c_str(), monitor, NULL);
	window = glfwCreateWindow(screenWidth, screenHeight, windowName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
	glViewport(0, 0, screenWidth, screenHeight);
	// 启用深度测试
	glEnable(GL_DEPTH_TEST);
	// 启用混合
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 取消粘滞键
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
	// 设置摄像机位置
	cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
	// 设置回调
	glfwSetKeyCallback(window, Game::KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallBack);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	Text::Init(screenWidth, screenHeight);
	Text::LoadFont("HarmonyOS_Sans_SC_Regular.ttf", 48);
	Rectangle::Init(screenWidth, screenHeight);
	Cube::Init();
}

void OpenGL::Update()
{
	double currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime); // 计算每帧时间间隔（秒）
	lastTime = currentTime;					   // 更新 lastTime
	glfwSwapBuffers(window);
	mouseEnter = false;
	glfwPollEvents();
	if (!mouseEnter && !mouseDragging)
	{
		glm::mat4 matrix(1.0f);
		if (abs(xoffset) > 0.0001f)
		{
			xoffset *= 0.9f;
			matrix = glm::rotate(matrix, xoffset * sensitivity, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (abs(yoffset) > 0.0001f)
		{
			yoffset *= 0.9f;
			matrix = glm::rotate(matrix, xoffset * sensitivity, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		rotationMatrix = matrix * rotationMatrix;
	}
}

bool OpenGL::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void OpenGL::Terminate()
{
	glfwTerminate();
}
void OpenGL::MouseCallBack(GLFWwindow *window, double xpos, double ypos)
{
	mouseEnter = true;
	if (!mouseDragging)
	{
		glm::mat4 matrix(1.0f);
		if (abs(xoffset) > 0.0001f)
		{
			xoffset *= 0.9f;
			matrix = glm::rotate(matrix, xoffset * sensitivity, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (abs(yoffset) > 0.0001f)
		{
			yoffset *= 0.9f;
			matrix = glm::rotate(matrix, xoffset * sensitivity, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		rotationMatrix = matrix * rotationMatrix;
	}
	else
	{
		xoffset = float(xpos - lastX);
		yoffset = float(ypos - lastY);
		lastX = xpos;
		lastY = ypos;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		glm::mat4 mat(1.0f);
		mat = glm::rotate(mat, xoffset * sensitivity, glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, yoffset * sensitivity, glm::vec3(1.0f, 0.0f, 0.0f));
		rotationMatrix = mat * rotationMatrix;
	}
}

void OpenGL::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			mouseDragging = true;
			glfwGetCursorPos(window, &lastX, &lastY); // 记录鼠标按下时的位置
		}
		else if (action == GLFW_RELEASE)
		{
			mouseDragging = false; // 松开鼠标停止拖动
		}
	}
}