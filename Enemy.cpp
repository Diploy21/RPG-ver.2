#include "Enemy.h"
#include "Player.h"
#include "Source.h"

int Enemy::ID = 0;

Enemy::Enemy(string SetName, char Map[y][x], Player &P)
{
	srand(time(NULL));

	EnemyPositionX = rand() % x + 1;
	EnemyPositionY = rand() % y + 1;

	EnemyEndMoveX = rand() % x + 1;
	EnemyEndMoveY = rand() % y + 1;

	bool flagPosition = false;
	bool flagMove = false;
	while (!flagPosition)
	{
		if (Map[EnemyPositionY][EnemyPositionX] == ' ')
		{
			Map[EnemyPositionY][EnemyPositionX] = Sign;
			flagPosition = true;
			break;
		}
		EnemyPositionX = rand() % x + 1;
		EnemyPositionY = rand() % y + 1;

	}

	while (!flagMove)
	{
		if (Map[EnemyEndMoveY][EnemyEndMoveX] == ' ')
		{
			flagMove = true;
			break;
		}
		EnemyEndMoveX = rand() % x + 1;
		EnemyEndMoveY = rand() % y + 1;

	}

	counter = 1;
	Coping_Map(copy_Map_Int, Map, P);
	copy_Map_Int[EnemyEndMoveY][EnemyEndMoveX] = 1;

	Building_Shortest_Path(EnemyPositionY, EnemyPositionX, counter, copy_Map_Int);

	Health = 100;
	Armor = 2;
	Name = SetName;
	ID++;
}

//реализация движения
void Enemy::EnemyAI_Move(char Map[y][x], Player& P)
{
	Update_Coping_Map(copy_Map_Int, Map, P);

	if (EnemyPositionY == EnemyEndMoveY && EnemyPositionX == EnemyEndMoveX)
	{
		Coping_Map(copy_Map_Int, Map, P);

		bool flagMove = false;
		while (!flagMove)
		{
			if (Map[EnemyEndMoveY][EnemyEndMoveX] == ' ')
			{
				flagMove = true;
				break;
			}
			EnemyEndMoveX = rand() % x + 1;
			EnemyEndMoveY = rand() % y + 1;

		}
		counter = 1;
		copy_Map_Int[EnemyEndMoveY][EnemyEndMoveX] = 1;
		Building_Shortest_Path(EnemyPositionY, EnemyPositionX, counter, copy_Map_Int);
	}

	if (Check_Player_Position(EnemyPositionY, EnemyPositionX, Map, P)) //Блок отвечает за поиск в радиусе игрока, если нашел движется к нему.
	{
		Coping_Map(copy_Map_Int, Map, P);
		counter = 1;
		copy_Map_Int[EnemyEndMoveY][EnemyEndMoveX] = 1;
		Building_Shortest_Path(EnemyPositionY, EnemyPositionX, counter, copy_Map_Int);
		
	}

	Enemy_Move(EnemyPositionY, EnemyPositionX, copy_Map_Int, Map, P);

}

//Волновой алгоритм построения пути до цели
void Enemy::Building_Shortest_Path(int EnemyPositionY, int EnemyPositionX, int& counter, int copyMapInt[y][x])
{
	while (Path_Finder_Check(copyMapInt, EnemyPositionY, EnemyPositionX, counter))
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
	counter--;

	/*for (int i = 1; i < y - 1; i++)
	{
		for (int j = 1; j < x - 1; j++)
		{
			cout << copyMapInt[i][j];
		}
		cout << endl;
	}*/

}

//Функция проверяет нашел ли алгоритм коненую точку массива или заполнил весь массив(Реверсивно применяется для движения)
bool Enemy::Path_Finder_Check(int copyMapInt[y][x], int Enemy_Move_Y, int Enemy_Move_X, int counter)
{
	bool state = false;

	for (int i = 1; i < y - 1; i++)
	{
		for (int j = 1; j < x - 1; j++)
		{
			if (copyMapInt[i][j] == 0)
			{
				state = true;
				break;
			}
		}
	}
	if (copyMapInt[Enemy_Move_Y][Enemy_Move_X] == counter)
	{
		state = false;
	}
	return state;
}

//Функция движения по найденному маршруту
void Enemy::Enemy_Move(int& EnemyPositionY, int& EnemyPositionX, int copyMapInt[y][x], char Map[y][x], Player &P)
{
	if (Path_Finder_Check(copyMapInt, EnemyPositionY, EnemyPositionX, counter) && counter)
	{
		if (copyMapInt[EnemyPositionY - 1][EnemyPositionX] == counter)
		{
			copyMapInt[EnemyPositionY][EnemyPositionX] = 0;
			Map[EnemyPositionY][EnemyPositionX] = ' ';
			EnemyPositionY--;
			Map[EnemyPositionY][EnemyPositionX] = Sign;
			counter--;
		}
		else if (copyMapInt[EnemyPositionY + 1][EnemyPositionX] == counter)
		{
			copyMapInt[EnemyPositionY][EnemyPositionX] = 0;
			Map[EnemyPositionY][EnemyPositionX] = ' ';
			EnemyPositionY++;
			Map[EnemyPositionY][EnemyPositionX] = Sign;
			counter--;
		}
		else if (copyMapInt[EnemyPositionY][EnemyPositionX - 1] == counter)
		{
			copyMapInt[EnemyPositionY][EnemyPositionX] = 0;
			Map[EnemyPositionY][EnemyPositionX] = ' ';
			EnemyPositionX--;
			Map[EnemyPositionY][EnemyPositionX] = Sign;
			counter--;
		}
		else if (copyMapInt[EnemyPositionY][EnemyPositionX + 1] == counter)
		{
			copyMapInt[EnemyPositionY][EnemyPositionX] = 0;
			Map[EnemyPositionY][EnemyPositionX] = ' ';
			EnemyPositionX++;
			Map[EnemyPositionY][EnemyPositionX] = Sign;
			counter--;
		}
		else
		{
			Coping_Map(copyMapInt, Map, P);
			counter = 1;
			copyMapInt[EnemyEndMoveY][EnemyEndMoveX] = 1;
			Building_Shortest_Path(EnemyPositionY, EnemyPositionX, counter, copyMapInt);
		}

	}
}

//функция проверяте есть ли игрок в области видимости, возвраащет его координаты и истину если есть
bool Enemy::Check_Player_Position(int& EnemyPositionY, int& EnemyPositionX, char Map[y][x], Player& P)
{
	bool state = false;
	for (int i = EnemyPositionY - 4; i < EnemyPositionY + 4; i++)
	{
		for (int j = EnemyPositionX - 4; j < EnemyPositionX + 4; j++)
		{
			if (i == P.PlayerPositionY && j == P.PlayerPositionX)
			{
				if (i > EnemyPositionY)
				{
					EnemyEndMoveY = i - 1;
				}
				else if (i < EnemyPositionY)
				{
					EnemyEndMoveY = i + 1;
				}
				else
				{
					EnemyEndMoveY = i;
				}

				if (j > EnemyPositionX)
				{
					EnemyEndMoveX = j - 1;
				}
				else if (j < EnemyPositionX)
				{
					EnemyEndMoveX = j + 1;
				}
				else
				{
					EnemyEndMoveX = j;
				}

				state = true;
				break;
			}

		}
	}

	return state;
}

//Копирование карты в целочисленный массив
void Enemy::Coping_Map(int copyMapInt[y][x], char Map[y][x], Player &P)
{
	for (int i = 0; i < y; i++) // <= 17
	{
		for (int j = 0; j < x; j++) // <= 36
		{
			if (Map[i][j] == 1 || Map[i][j] == 2)
			{
				copyMapInt[i][j] = 0;
			}
			else if (i == P.PlayerPositionY && j == P.PlayerPositionX)
			{
				copyMapInt[i][j] = -2;
			}
			else if (Map[i][j] != ' ')
			{
				copyMapInt[i][j] = -3;
			}
			else
			{
				copyMapInt[i][j] = 0;
			}
		}
	}
}

//Обновление карты
void Enemy::Update_Coping_Map(int copyMapInt[y][x], char Map[y][x], Player& P)
{
	int TempMap[y][x];
	Coping_Map(TempMap, Map, P);
	int count = 0;

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (copyMapInt[i][j] == -2)
			{
				copyMapInt[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (TempMap[i][j] == -2)
			{
				copyMapInt[P.PlayerPositionY][P.PlayerPositionX] = -2;
			}
		}
	}

	Building_Shortest_Path(EnemyPositionY, EnemyPositionX, counter, copyMapInt);
}



Enemy::~Enemy()
{
	Sign = ' ';
}
