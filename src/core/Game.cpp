#include "Game.h"

void Game::Init()
{
	Game::grid[rand() % 4 + 1][rand() % 4 + 1] = 2;
	srand(time(nullptr));
}

void Game::Update()
{
	char inputKey = _getch();
	if (inputKey != 'w' && inputKey != 's' && inputKey != 'a' && inputKey != 'd')
		return;
	std::cout << inputKey << std::endl;
	// 记录操作前的状态
	static int record[SIZE][SIZE];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			record[i][j] = grid[i][j];
	// 旋转至向上
	int revolveTime = (inputKey == 'a')	  ? 1
					  : (inputKey == 's') ? 2
					  : (inputKey == 'd') ? 3
										  : 0;
	for (int i = 0; i < revolveTime; i++)
		Revolve();
	// 向上压缩
	Compress();
	// 合并
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 4; j++)
		{
			if (grid[i][j] == grid[i + 1][j])
			{
				grid[i][j] *= 2;
				grid[i + 1][j] = 0;
				score += grid[i][j];
			}
		}
	// 再次压缩
	Compress();
	// 旋转还原
	revolveTime = (4 - revolveTime) % 4;
	for (int i = 0; i < revolveTime; i++)
		Revolve();
	// 检测是否有移动,并且有空位
	bool changed = false, remain = false;
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (record[i][j] != grid[i][j])
			{
				changed = true;
			}
			if (grid[i][j] == 0)
			{
				remain = true;
			}
		}
		if (changed && remain)
			break;
	}
	// 满足条件，随机生成一个2或4
	if (changed && remain)
	{
		int x, y;
		do
		{
			x = rand() % 4 + 1;
			y = rand() % 4 + 1;
		} while (grid[x][y] != 0);
		// 80%生成2，20%生成4
		grid[x][y] = rand() % 5 ? 2 : 4;
	}
	// 判断游戏结束
	if (!changed && !remain)
	{
		gameOver = true;
	}
}

// 顺时针旋转90度
void Game::Revolve()
{
	static int temp[SIZE][SIZE];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
		{
			temp[i][j] = grid[5 - j][i];
		}
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
		{
			grid[i][j] = temp[i][j];
		}
}

void Game::Compress()
{
	for (int k = 0; k < 3; k++)
		for (int i = 1; i <= 3; i++)
			for (int j = 1; j <= 4; j++)
			{
				if (grid[i][j] == 0)
				{
					int temp = grid[i][j];
					grid[i][j] = grid[i + 1][j];
					grid[i + 1][j] = temp;
				}
			}
}

void Game::Print()
{
	system("cls");
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			std::cout << std::setw(5) << grid[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "\nscore: " << score << std::endl;
}

bool Game::gameOver = false;

int Game::grid[SIZE][SIZE];
int Game::score;