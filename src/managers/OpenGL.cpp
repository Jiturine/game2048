#include "OpenGL.h"

unsigned int OpenGL::screenWidth;
unsigned int OpenGL::screenHeight;
std::string OpenGL::windowName;
GLFWwindow *OpenGL::window;
double OpenGL::lastX;
double OpenGL::lastY;
bool OpenGL::mouseDragging;
float OpenGL::yaw;
float OpenGL::pitch;
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
	glfwSetKeyCallback(window, Game3D::KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallBack);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	// 文字投影矩阵设置
	Text::Init(screenWidth, screenHeight);
	Rectangle::Init(screenWidth, screenHeight);
	Cube::Init();
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
void OpenGL::MouseCallBack(GLFWwindow *window, double xpos, double ypos)
{
	if (!mouseDragging)
		return;

	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f; // 控制灵敏度
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	glm::mat4 mat(1.0f);
	mat = glm::rotate(mat, xoffset * sensitivity, glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::rotate(mat, yoffset * sensitivity, glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = mat * rotationMatrix;
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