#include "Game.h"

void Game::Init()
{
	srand(time(nullptr));
	int i, j, k;
	do
	{
		i = rand() % 4 + 1;
		j = rand() % 4 + 1;
		k = rand() % 4 + 1;
	} while ((i == 2 || i == 3) && (j == 2 || j == 3) && (k == 2 || k == 3));
	Game::grid[i][j][k] = 2;
}

void Game::RevolveX()
{
	static int temp[SIZE][SIZE][SIZE];
	for (int x = 1; x <= 4; x++)
		for (int y = 1; y <= 4; y++)
			for (int z = 1; z <= 4; z++)
			{
				temp[x][y][z] = grid[x][5 - z][y];
			}
	for (int x = 1; x <= 4; x++)
		for (int y = 1; y <= 4; y++)
			for (int z = 1; z <= 4; z++)
			{
				grid[x][y][z] = temp[x][y][z];
			}
}
void Game::RevolveY()
{
	static int temp[SIZE][SIZE][SIZE];
	for (int x = 1; x <= 4; x++)
		for (int y = 1; y <= 4; y++)
			for (int z = 1; z <= 4; z++)
			{
				temp[x][y][z] = grid[5 - z][y][x];
			}
	for (int x = 1; x <= 4; x++)
		for (int y = 1; y <= 4; y++)
			for (int z = 1; z <= 4; z++)
			{
				grid[x][y][z] = temp[x][y][z];
			}
}

void Game::Compress()
{
	for (int k = 0; k < 3; k++)
		for (int x = 1; x <= 4; x++)
			for (int y = 1; y <= 4; y++)
			{
				if ((x == 2 || x == 3) && (y == 2 || y == 3))
					continue;
				for (int z = 1; z <= 3; z++)
				{
					if (grid[x][y][z] == 0)
					{
						int temp = grid[x][y][z];
						grid[x][y][z] = grid[x][y][z + 1];
						grid[x][y][z + 1] = temp;
					}
				}
			}
}

void Game::Update()
{
	if (!inputKey)
		return;
	// 记录操作前的状态
	static int record[SIZE][SIZE][SIZE];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			for (int k = 1; k <= 4; k++)
				record[i][j][k] = grid[i][j][k];
	glm::vec4 normals[6] = {
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),	// 前面 (正Z)
		glm::vec4(0.0f, 0.0f, -1.0f, 0.0f), // 后面 (负Z)
		glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f), // 左面 (负X)
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),	// 右面 (正X)
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),	// 上面 (正Y)
		glm::vec4(0.0f, -1.0f, 0.0f, 0.0f)	// 下面 (负Y)
	};
	for (int i = 0; i < 6; i++)
	{
		normals[i] = OpenGL::rotationMatrix * normals[i];
	}
	glm::vec3 direction = (inputKey == 'w')	  ? glm::vec3(0.0f, 1.0f, 0.0f)
						  : (inputKey == 's') ? glm::vec3(0.0f, -1.0f, 0.0f)
						  : (inputKey == 'a') ? glm::vec3(-1.0f, 0.0f, 0.0f)
						  : (inputKey == 'd') ? glm::vec3(1.0f, 0.0f, 0.0f)
						  : (inputKey == 'q') ? glm::vec3(0.0f, 0.0f, 1.0f)
						  : (inputKey == 'e') ? glm::vec3(0.0f, 0.0f, -1.0f)
											  : glm::vec3(0.0f);
	int maxDotIndex = 0;
	float maxDotValue = -1.0f;
	for (int i = 0; i < 6; ++i)
	{
		if (maxDotValue < glm::dot(glm::vec3(normals[i]), direction))
		{
			maxDotIndex = i;
			maxDotValue = glm::dot(glm::vec3(normals[i]), direction);
		}
	}
	char targetFace = (maxDotIndex == 0)   ? 'q'
					  : (maxDotIndex == 1) ? 'e'
					  : (maxDotIndex == 2) ? 'a'
					  : (maxDotIndex == 3) ? 'd'
					  : (maxDotIndex == 4) ? 'w'
					  : (maxDotIndex == 5) ? 's'
										   : '\0';
	// 旋转至向底面
	int revolveTime = (targetFace == 'q')	? 1 // 绕Y轴顺时针
					  : (targetFace == 'w') ? 2 // 绕Y轴顺时针
					  : (targetFace == 'e') ? 3 // 绕Y轴顺时针
					  : (targetFace == 's') ? 0
					  : (targetFace == 'a') ? 3	 // 绕X轴顺时针
											: 1; // 绕X轴顺时针
	for (int i = 0; i < revolveTime; i++)
	{
		if (targetFace == 'q' || targetFace == 'w' || targetFace == 'e' || targetFace == 's')
		{
			RevolveY();
		}
		else
		{
			RevolveX();
		}
	}
	// 向底面压缩
	Compress();
	// 合并
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
		{
			if ((i == 2 || i == 3) && (j == 2 || j == 3))
				continue;
			for (int k = 1; k <= 3; k++)
			{
				if (grid[i][j][k] == grid[i][j][k + 1])
				{
					grid[i][j][k] *= 2;
					grid[i][j][k + 1] = 0;
					score += grid[i][j][k];
				}
			}
		}

	// 再次压缩
	Compress();
	// 旋转还原
	revolveTime = (4 - revolveTime) % 4;
	for (int i = 0; i < revolveTime; i++)
	{
		if (targetFace == 'q' || targetFace == 'w' || targetFace == 'e' || targetFace == 's')
		{
			RevolveY();
		}
		else
		{
			RevolveX();
		}
	}
	// 检测是否有移动,并且有空位
	bool changed = false, remain = false;
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			for (int k = 1; k <= 4; k++)
			{
				if ((i == 2 || i == 3) && (j == 2 || j == 3) && (k == 2 || k == 3))
					continue;
				if (record[i][j][k] != grid[i][j][k])
				{
					changed = true;
				}
				if (grid[i][j][k] == 0)
				{
					remain = true;
				}
			}
			if (changed && remain)
				break;
		}
		if (changed && remain)
			break;
	}
	// 满足条件，随机生成一个2或4
	if (changed && remain)
	{
		int i, j, k;
		do
		{
			i = rand() % 4 + 1;
			j = rand() % 4 + 1;
			k = rand() % 4 + 1;
		} while (((i == 2 || i == 3) && (j == 2 || j == 3) && (k == 2 || k == 3)) || grid[i][j][k] != 0);
		// 80%生成2，20%生成4
		grid[i][j][k] = rand() % 5 ? 2 : 4;
	}
	// 判断游戏结束
	if (!changed && !remain)
	{
		gameOver = true;
	}
	inputKey = 0;
}

void Game::Print()
{
	system("cls");
	for (int x = 1; x <= 4; x++)
	{
		for (int y = 1; y <= 4; y++)
		{
			for (int z = 1; z <= 4; z++)
			{
				std::cout << std::setw(5) << grid[x][y][z];
			}
			std::cout << "\n";
		}
		std::cout << "\n\n";
	}
	std::cout << "\nscore: " << score << std::endl;
}

void Game::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
		{
			inputKey = 'w';
		}
		else if (key == GLFW_KEY_S)
		{
			inputKey = 's';
		}
		else if (key == GLFW_KEY_A)
		{
			inputKey = 'a';
		}
		else if (key == GLFW_KEY_D)
		{
			inputKey = 'd';
		}
		else if (key == GLFW_KEY_Q)
		{
			inputKey = 'q';
		}
		else if (key == GLFW_KEY_E)
		{
			inputKey = 'e';
		}
	}
}

int Game::grid[SIZE][SIZE][SIZE];
int Game::score;
bool Game::gameOver;
char Game::inputKey;