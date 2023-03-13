#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>

#include "Header.h"

using namespace std;


// ожидание
void Sleep()
{
	this_thread::sleep_for(chrono::nanoseconds(2000000000));
}

// читска консоли
void clear() 
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

//  Map block
void RenderMap(char Map[y][x])
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (i == 0 && j == 0)
			{
				Map[i][j] = 201;
			}
			else if (i == y - 1 && j == 0)
			{
				Map[i][j] = 200;
			}
			else if (i == 0 && j == x - 1)
			{
				Map[i][j] = 187;
			}
			else if (i == y - 1 && j == x - 1)
			{
				Map[i][j] = 188;
			}
			else if (i == 0 || i == y - 1)
			{
				Map[i][j] = 205;
			}
			else if (j == 0 || j == x - 1)
			{
				Map[i][j] = 186;
			}
			else
			{
				Map[i][j] = ' ';
			}
		}
	}
}

void output(char Map[y][x], int H, int A, int G)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (i == 0 && j == x - 1)
			{
				cout << Map[i][j] << "\t Health - " << H;
			}
			else if (i == 1 && j == x - 1)
			{
				cout << Map[i][j] << "\t Armor  - " << A;
			}
			else if (i == 2 && j == x - 1)
			{
				cout << Map[i][j] << "\t Gold   - " << G;
			}
			else
			{
				cout << Map[i][j];
			}
		}
		cout << endl;
	}
}


// Enemy block

Enemy::Enemy(char Map[y][x])
{
	srand(time(NULL));

	Enemy_Position_X = rand() % x + 1;
	Enemy_Position_Y = rand() % y + 1;

	Enemy_End_Move_X = rand() % x + 1;
	Enemy_End_Move_Y = rand() % y + 1;

	bool flagPosition = false;
	bool flagMove = false;
	while (!flagPosition)
	{
		if (Map[Enemy_Position_Y][Enemy_Position_X] == ' ')
		{
			Map[Enemy_Position_Y][Enemy_Position_X] = Sign;
			flagPosition = true;
			break;
		}
		Enemy_Position_X = rand() % x + 1;
		Enemy_Position_Y = rand() % y + 1;

	}

	while (!flagMove)
	{
		if (Map[Enemy_End_Move_Y][Enemy_End_Move_X] == ' ')
		{
			flagMove = true;
			break;
		}
		Enemy_End_Move_X = rand() % x + 1;
		Enemy_End_Move_Y = rand() % y + 1;

	}

	counter = 1;
	copyMapInt[Enemy_End_Move_Y][Enemy_End_Move_X] = counter;

	Health = 100;
	Arnmor = 1;
	Gold = 10;
}


//реализация движения
void Enemy::EnemyAI_Move(char Map[y][x])
{
	CopingMap(copyMapInt, Map);

	if (Enemy_Position_Y == Enemy_End_Move_Y && Enemy_Position_X == Enemy_End_Move_X)
	{
		Enemy_End_Move_X = rand() % x + 1;
		Enemy_End_Move_Y = rand() % y + 1;
		copyMapInt[Enemy_End_Move_Y][Enemy_End_Move_X] = counter;
	}
	if (CheckPlayerPosition(Enemy_End_Move_Y, Enemy_End_Move_X, Map))
	{
		BuildingShortestPath(Enemy_Position_Y, Enemy_Position_X, counter, copyMapInt);
		EnemyMove(Enemy_End_Move_Y, Enemy_End_Move_X, copyMapInt, Map);
	}
	else 
	{
		BuildingShortestPath(Enemy_Position_Y, Enemy_Position_X, counter, copyMapInt);
		EnemyMove(Enemy_End_Move_Y, Enemy_End_Move_X, copyMapInt, Map);
	}

	ClearCopingMap(copyMapInt);
}

//Волновой алгоритм построения пути до цели
void Enemy::BuildingShortestPath(int Enemy_Position_Y, int Enemy_Position_X, int& counter, int copyMapInt[y][x])
{
	while (PathFinderCheck(copyMapInt, Enemy_Position_X, Enemy_Position_Y, counter))
	{
		for (int i = 1; i < y - 1; i++)
		{
			for (int j = 1; j < x - 1; j++)
			{
				if (copyMapInt[i][j] == counter)
				{
					if (copyMapInt[i - 1][j] == 0)
					{
						copyMapInt[i - 1][j] = counter + 1;
					}
					if (copyMapInt[i + 1][j] == 0)
					{
						copyMapInt[i + 1][j] = counter + 1;
					}
					if (copyMapInt[i][j - 1] == 0)
					{
						copyMapInt[i][j - 1] = counter + 1;
					}
					if (copyMapInt[i][j + 1] == 0)
					{
						copyMapInt[i][j + 1] = counter + 1;
					}
				}
			}
		}
		counter++;
	}
}

//Копирование карты в целочисленный массив
void Enemy::CopingMap(int copyMapInt[y][x], char Map[y][x])
{
	for (int i = 0; i < y; i++) // <= 17
	{
		for (int j = 0; j < x; j++) // <= 36
		{
			if (Map[i][j] != ' ')
			{
				copyMapInt[i][j] = -1;
			}
			else if (Map[i][j] == 2)
			{
				copyMapInt[i][j] = 0;
			}
			else
			{
				copyMapInt[i][j] = 0;
			}
		}
	}
}

void Enemy::ClearCopingMap(int copyMapInt[y][x])
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			copyMapInt[i][j] = 0;
		}
	}
}

//Функция проверяет нашел ли алгоритм коненую точку массива или заполнил весь массив(Реверсивно применяется для движения)
bool Enemy::PathFinderCheck(int copyMapInt[y][x], int Enemy_End_Move_Y, int Enemy_End_Move_X, int counter)
{
	bool state = false;

	for (int i = 1; i < y - 1; i++)
	{
		for (int j = 1; j < x - 1; j++)
		{
			if (copyMapInt[i][j] == 0)
			{
				state = true;
			}
		}
	}
	if (copyMapInt[Enemy_End_Move_Y][Enemy_End_Move_X] == counter)
	{
		state = false;
	}
	return state;
}

//Функция движения по найденному маршруту
void Enemy::EnemyMove(int& Enemy_End_Move_Y, int& Enemy_End_Move_X, int copyMapInt[y][x], char Map[y][x])
{
	if (PathFinderCheck(copyMapInt, Enemy_End_Move_Y, Enemy_End_Move_X, counter))
	{
		if (copyMapInt[Enemy_Position_Y - 1][Enemy_Position_X] == counter)
		{
			copyMapInt[Enemy_Position_Y][Enemy_Position_X] = 0;
			Map[Enemy_Position_Y][Enemy_Position_X] = ' ';
			Enemy_Position_Y--;
			Map[Enemy_Position_Y][Enemy_Position_X] = Sign;
			counter--;
		}
		if (copyMapInt[Enemy_Position_Y + 1][Enemy_Position_X] == counter)
		{
			copyMapInt[Enemy_Position_Y][Enemy_Position_X] = 0;
			Map[Enemy_Position_Y][Enemy_Position_X] = ' ';
			Enemy_Position_Y++;
			Map[Enemy_Position_Y][Enemy_Position_X] = Sign;
			counter--;
		}
		if (copyMapInt[Enemy_Position_Y][Enemy_Position_X - 1] == counter)
		{
			copyMapInt[Enemy_Position_Y][Enemy_Position_X] = 0;
			Map[Enemy_Position_Y][Enemy_Position_X] = ' ';
			Enemy_Position_X--;
			Map[Enemy_Position_Y][Enemy_Position_X] = Sign;
			counter--;
		}
		if (copyMapInt[Enemy_Position_Y][Enemy_Position_X + 1] == counter)
		{
			copyMapInt[Enemy_Position_Y][Enemy_Position_X] = 0;
			Map[Enemy_Position_Y][Enemy_Position_X] = ' ';
			Enemy_Position_X++;
			Map[Enemy_Position_Y][Enemy_Position_X] = Sign;
			counter--;
		}
	}
}

//функция проверяте есть ли игрок в области видимости, возвраащет его координаты и истину если есть
bool Enemy::CheckPlayerPosition(int& Enemy_End_Move_Y, int& Enemy_End_Move_X, char Map[y][x])
{
	bool state = false;
	for (int i = Enemy_Position_Y - 4; i < Enemy_Position_Y + 4; i++)
	{
		for (int j = Enemy_Position_X - 4; j < Enemy_Position_X + 4; j++)
		{
			if (Map[i][j] == 2)
			{
				if (i > Enemy_Position_Y)
				{
					Enemy_End_Move_Y = i - 1;
				}
				else if (i < Enemy_Position_Y) 
				{
					Enemy_End_Move_Y = i + 1;
				}
				else
				{
					Enemy_End_Move_Y = i;
				}

				if (j > Enemy_Position_X)
				{
					Enemy_End_Move_X = j - 1;
				}
				else if (j > Enemy_Position_X)
				{
					Enemy_End_Move_X = j + 1;
				}
				else
				{
					Enemy_End_Move_X = j;
				}

				state = true;
				break;
			}
			
		}
	}
	return state;
}


Enemy::~Enemy()
{

}


// Player block

//движение игрока, возвращает ложь если нажата О( используется для завершения игры
bool Player::PlayerMove(bool state, char Map[y][x])
{
	switch (_getch())
	{
	case 'w':
		if (Map[Player_Position_Y - 1][Player_Position_X] == ' ')
		{
			Map[Player_Position_Y][Player_Position_X] = ' ';
			Player_Position_Y--;
			Map[Player_Position_Y][Player_Position_X] = Sign;
		}
		break;
	case 's':
		if (Map[Player_Position_Y + 1][Player_Position_X] == ' ')
		{
			Map[Player_Position_Y][Player_Position_X] = ' ';
			Player_Position_Y++;
			Map[Player_Position_Y][Player_Position_X] = Sign;
			system("cls");
			output(Map, Health, Arnmor, Gold);
		}
		break;
	case 'd':
		if (Map[Player_Position_Y][Player_Position_X + 1] == ' ')
		{
			Map[Player_Position_Y][Player_Position_X] = ' ';
			Player_Position_X++;
			Map[Player_Position_Y][Player_Position_X] = Sign;
		}
		break;
	case 'a':
		if (Map[Player_Position_Y][Player_Position_X - 1] == ' ')
		{
			Map[Player_Position_Y][Player_Position_X] = ' ';
			Player_Position_X--;
			Map[Player_Position_Y][Player_Position_X] = Sign;
		}
		break;
	case 'o':
		state = false;
		break;
	default:
		break;
	}
	return state;
}

Player::Player(char Map[y][x])
{
	srand(time(NULL));
	bool flag = false;

	Player_Position_X = rand() % 49 + 1;
	Player_Position_Y = rand() % 24 + 1;
	while (!flag)
	{
		if (Map[Player_Position_Y][Player_Position_X] == ' ')
		{
			Map[Player_Position_Y][Player_Position_X] = Sign;
			flag = true;
			break;
		}
		Player_Position_X = rand() % 49 + 1;
		Player_Position_Y = rand() % 24 + 1;
	}
	Health = 100;
	Arnmor = 1;
	Gold = 10;
}

Player::~Player()
{

}
