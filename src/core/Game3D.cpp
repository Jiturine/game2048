#include "Game3D.h"

void Game3D::Init()
{
	srand(time(nullptr));
	int i, j, k;
	do
	{
		i = rand() % 4 + 1;
		j = rand() % 4 + 1;
		k = rand() % 4 + 1;
	} while ((i == 2 || i == 3) && (j == 2 || j == 3) && (k == 2 || k == 3));
	Game3D::grid[i][j][k] = 2;
}

void Game3D::RevolveX()
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
void Game3D::RevolveY()
{
	static int temp[SIZE][SIZE][SIZE];
	for (int x = 1; x <= 4; x++)
		for (int y = 1; y <= 4; y++)
			for (int z = 1; z <= 4; z++)
			{
				temp[x][y][z] = grid[z][y][5 - x];
			}
	for (int x = 1; x <= 4; x++)
		for (int y = 1; y <= 4; y++)
			for (int z = 1; z <= 4; z++)
			{
				grid[x][y][z] = temp[x][y][z];
			}
}

void Game3D::Compress()
{
	for (int k = 0; k < 3; k++)
		for (int x = 1; x <= 4; x++)
			for (int y = 1; y <= 4; y++)
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
void Game3D::Print()
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
int Game3D::grid[SIZE][SIZE][SIZE];
int Game3D::score;
bool Game3D::gameOver;