#include "Game.h"

void Game::Init()
{
	srand(time(nullptr));
	score = 0;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			for (int k = 1; k <= 4; k++)
			{
				grid[i][j][k].num = 0;
				grid[i][j][k].preNum = 0;
				grid[i][j][k].indexOfNum = {0, 0, 0};
				grid[i][j][k].indexOfMergedNum = {0, 0, 0};
				grid[i][j][k].targetIndex = {i, j, k};
			}
	int i, j, k;
	do
	{
		i = rand() % 4 + 1;
		j = rand() % 4 + 1;
		k = rand() % 4 + 1;
	} while ((i == 2 || i == 3) && (j == 2 || j == 3) && (k == 2 || k == 3));
	grid[i][j][k].num = 2;
	grid[i][j][k].preNum = 2;
	grid[i][j][k].indexOfNum = {i, j, k};
}

// 绕X轴顺时针旋转90° (向X轴负方向看)
void Game::RevolveX()
{
	static Grid tempGrid[SIZE][SIZE][SIZE];
	for (int x = 1; x <= 4; x++)
		for (int y = 1; y <= 4; y++)
			for (int z = 1; z <= 4; z++)
			{
				tempGrid[x][y][z].num = grid[x][5 - z][y].num;
				tempGrid[x][y][z].indexOfNum = grid[x][5 - z][y].indexOfNum;
				tempGrid[x][y][z].indexOfMergedNum = grid[x][5 - z][y].indexOfMergedNum;
			}
	for (int x = 1; x <= 4; x++)
		for (int y = 1; y <= 4; y++)
			for (int z = 1; z <= 4; z++)
			{
				grid[x][y][z].num = tempGrid[x][y][z].num;
				grid[x][y][z].indexOfNum = tempGrid[x][y][z].indexOfNum;
				grid[x][y][z].indexOfMergedNum = tempGrid[x][y][z].indexOfMergedNum;
			}
}

// 绕Y轴顺时针旋转90° (向Y轴负方向看)
void Game::RevolveY()
{
	static Grid tempGrid[SIZE][SIZE][SIZE];
	for (int x = 1; x <= 4; x++)
		for (int y = 1; y <= 4; y++)
			for (int z = 1; z <= 4; z++)
			{
				tempGrid[x][y][z].num = grid[z][y][5 - x].num;
				tempGrid[x][y][z].indexOfNum = grid[z][y][5 - x].indexOfNum;
				tempGrid[x][y][z].indexOfMergedNum = grid[z][y][5 - x].indexOfMergedNum;
			}
	for (int x = 1; x <= 4; x++)
		for (int y = 1; y <= 4; y++)
			for (int z = 1; z <= 4; z++)
			{
				grid[x][y][z].num = tempGrid[x][y][z].num;
				grid[x][y][z].indexOfNum = tempGrid[x][y][z].indexOfNum;
				grid[x][y][z].indexOfMergedNum = tempGrid[x][y][z].indexOfMergedNum;
			}
}

// 向后压缩
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
					if (grid[x][y][z].num == 0 && grid[x][y][z + 1].num != 0)
					{
						std::swap(grid[x][y][z].num, grid[x][y][z + 1].num);
						std::swap(grid[x][y][z].indexOfNum, grid[x][y][z + 1].indexOfNum);
						std::swap(grid[x][y][z].indexOfMergedNum, grid[x][y][z + 1].indexOfMergedNum);
					}
				}
			}
}

void Game::Update()
{
	elapsedTime += OpenGL::deltaTime;
	if (elapsedTime > totalTime && !numChanged)
	{
		numChanged = true;
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				for (int k = 1; k <= 4; k++)
				{
					grid[i][j][k].preNum = grid[i][j][k].num;
					grid[i][j][k].indexOfNum = {i, j, k};
				}
	}
	if (!inputKey)
		return;
	if (!numChanged)
	{
		numChanged = true;
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				for (int k = 1; k <= 4; k++)
				{
					grid[i][j][k].preNum = grid[i][j][k].num;
					grid[i][j][k].indexOfNum = {i, j, k};
				}
	}
	// 记录操作前的状态
	static int recordNum[SIZE][SIZE][SIZE];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			for (int k = 1; k <= 4; k++)
				recordNum[i][j][k] = grid[i][j][k].num;
	char targetFace = GetTargetFace();
	// 旋转至向后面
	int revolveTime = (targetFace == 'a')	? 1 // 绕Y轴顺时针
					  : (targetFace == 'q') ? 2 // 绕Y轴顺时针
					  : (targetFace == 'd') ? 3 // 绕Y轴顺时针
					  : (targetFace == 'e') ? 0
					  : (targetFace == 's') ? 3	 // 绕X轴顺时针
											: 1; // 绕X轴顺时针
	for (int i = 0; i < revolveTime; i++)
	{
		if (targetFace == 'a' || targetFace == 'q' || targetFace == 'd' || targetFace == 'e')
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
				if (grid[i][j][k].num == grid[i][j][k + 1].num && grid[i][j][k].num != 0)
				{
					grid[i][j][k].num *= 2;
					grid[i][j][k + 1].num = 0;
					grid[i][j][k].indexOfMergedNum = grid[i][j][k + 1].indexOfNum;
					grid[i][j][k + 1].indexOfNum = {0, 0, 0};
					score += grid[i][j][k].num;
				}
			}
		}
	// 再次压缩
	Compress();
	// 旋转还原
	revolveTime = (4 - revolveTime) % 4;
	for (int i = 0; i < revolveTime; i++)
	{
		if (targetFace == 'a' || targetFace == 'q' || targetFace == 'd' || targetFace == 'e')
		{
			RevolveY();
		}
		else
		{
			RevolveX();
		}
	}
	int count = 0;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			for (int k = 1; k <= 4; k++)
			{
				if (grid[i][j][k].num != 0)
				{
					int x = grid[i][j][k].indexOfNum.x;
					int y = grid[i][j][k].indexOfNum.y;
					int z = grid[i][j][k].indexOfNum.z;
					grid[x][y][z].targetIndex = {i, j, k};
					int mx = grid[i][j][k].indexOfMergedNum.x;
					int my = grid[i][j][k].indexOfMergedNum.y;
					int mz = grid[i][j][k].indexOfMergedNum.z;
					grid[mx][my][mz].targetIndex = {i, j, k};
					grid[i][j][k].indexOfMergedNum = {0, 0, 0};
				}
			}
	// 检测是否有移动,并且有空位
	bool changed = false;
	int remain = 0;
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			for (int k = 1; k <= 4; k++)
			{
				if ((i == 2 || i == 3) && (j == 2 || j == 3) && (k == 2 || k == 3))
					continue;
				if (recordNum[i][j][k] != grid[i][j][k].num)
				{
					changed = true;
				}
				if (grid[i][j][k].num == 0)
				{
					remain++;
				}
			}
			if (changed && remain)
				break;
		}
		if (changed && remain)
			break;
	}
	// 满足条件，随机生成若干个2或4
	if (changed && remain)
	{
		int generateCount = remain / 28 + 1;
		for (int p = 0; p < generateCount; p++)
		{
			int i, j, k;
			do
			{
				i = rand() % 4 + 1;
				j = rand() % 4 + 1;
				k = rand() % 4 + 1;
			} while (((i == 2 || i == 3) && (j == 2 || j == 3) && (k == 2 || k == 3)) || grid[i][j][k].num != 0);
			// 80%生成2，20%生成4
			grid[i][j][k].num = rand() % 5 ? 2 : 4;
			grid[i][j][k].preNum = 0;
			grid[i][j][k].indexOfNum = {i, j, k};
			grid[i][j][k].targetIndex = {i, j, k};
		}
	}
	// 判断游戏结束
	if (!changed && !remain)
	{
		gameOver = true;
		ScoreManager::AddScore(score);
		SwitchState<GameOverState>();
	}
	inputKey = 0;
	elapsedTime = 0;
	numChanged = false;
}
char Game::GetTargetFace()
{
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
	return (maxDotIndex == 0)	? 'q'
		   : (maxDotIndex == 1) ? 'e'
		   : (maxDotIndex == 2) ? 'a'
		   : (maxDotIndex == 3) ? 'd'
		   : (maxDotIndex == 4) ? 'w'
		   : (maxDotIndex == 5) ? 's'
								: '\0';
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
				std::cout << std::setw(5) << grid[x][y][z].num;
			}
			for (int z = 1; z <= 4; z++)
			{
				std::cout << std::setw(15) << std::format("({},{},{})", grid[x][y][z].indexOfNum.x, grid[x][y][z].indexOfNum.y, grid[x][y][z].indexOfNum.z);
			}
			std::cout << "\n";
		}
		std::cout << "\n\n";
	}
	std::cout << "\nscore: " << score << std::endl;
}

Game::Grid Game::grid[SIZE][SIZE][SIZE];
int Game::score;
bool Game::gameOver;
char Game::inputKey;
float Game::elapsedTime;
bool Game::numChanged;
std::unique_ptr<GameState> Game::currentState;