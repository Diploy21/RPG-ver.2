#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>

#include "Header.h"

using namespace std;


// ��������
void Sleep1(unsigned a)
{
	this_thread::sleep_for(chrono::seconds(a));
}

//Menu
bool Menu(bool state)
{
	cout << "\t\t\t\t My Game\n";
	cout << "\t\t1 - Start game.\n";
	cout << "\t\t2 - Out.\n";
	int a;
	cin >> a;

	switch(a)
	{
	case 1:
		state = true;
		break;
	case 2:
		state = false;
		break;
	default:
		break;
	}
	return state;
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
	CopingMap(copyMapInt, Map);
	copyMapInt[Enemy_End_Move_Y][Enemy_End_Move_X] = 1;

	BuildingShortestPath(Enemy_Position_Y, Enemy_Position_X, counter, copyMapInt);

	Health = 100;
	Arnmor = 1;
}


//���������� ��������
void Enemy::EnemyAI_Move(char Map[y][x], Player& P)
{
	/*cout << "Enemy_Position_Y - " << Enemy_Position_Y << "|Enemy_Position_X - " << Enemy_Position_X << endl;
	cout << "|Enemy_End_Move_Y - " << Enemy_End_Move_Y << "|Enemy_End_Move_X - " << Enemy_End_Move_X << endl;
	cout << "EndEnemy POS - " << copyMapInt[Enemy_End_Move_Y][Enemy_End_Move_X] << "|" 
		<<  copyMapInt[Enemy_Position_Y][Enemy_Position_X] << " - Enemy POS | counter - " << counter << endl;
	cout << "Player_Position_Y - " << P.Player_Position_Y << "|Player_Position_X - " << P.Player_Position_X << endl;*/

	UpdateCopingMap(copyMapInt, Map, P);

	if (Enemy_Position_Y == Enemy_End_Move_Y && Enemy_Position_X == Enemy_End_Move_X)
	{
		CopingMap(copyMapInt, Map);

		bool flagMove = false;
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
		copyMapInt[Enemy_End_Move_Y][Enemy_End_Move_X] = 1;
		BuildingShortestPath(Enemy_Position_Y, Enemy_Position_X, counter, copyMapInt);
	}
	
	if (CheckPlayerPosition(Enemy_Position_Y, Enemy_Position_X, Map)) //���� �������� �� ����� � ������� ������, ��� ����� �������� � ����.
	{
		CopingMap(copyMapInt, Map);
		counter = 1;
		copyMapInt[Enemy_End_Move_Y][Enemy_End_Move_X] = 1;
		BuildingShortestPath(Enemy_Position_Y, Enemy_Position_X, counter, copyMapInt);
	}
	
	EnemyMove(Enemy_Position_Y, Enemy_Position_X, copyMapInt, Map);


	/*for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (copyMapInt[i][j] > 1)
				cout << "*";
			else
				cout << copyMapInt[i][j];
		}
		cout << endl;
	}*/

}

//�������� �������� ���������� ���� �� ����
void Enemy::BuildingShortestPath(int Enemy_Position_Y, int Enemy_Position_X, int& counter, int copyMapInt[y][x])
{
	while (PathFinderCheck(copyMapInt, Enemy_Position_Y, Enemy_Position_X, counter))
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
}

//������� ��������� ����� �� �������� ������� ����� ������� ��� �������� ���� ������(���������� ����������� ��� ��������)
bool Enemy::PathFinderCheck(int copyMapInt[y][x], int Enemy_Move_Y, int Enemy_Move_X, int counter)
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

//������� �������� �� ���������� ��������
void Enemy::EnemyMove(int& Enemy_Position_Y, int& Enemy_Position_X, int copyMapInt[y][x], char Map[y][x])
{
	if (PathFinderCheck(copyMapInt, Enemy_Position_Y, Enemy_Position_X, counter) && counter)
	{
		if (copyMapInt[Enemy_Position_Y - 1][Enemy_Position_X] == counter)
		{
			copyMapInt[Enemy_Position_Y][Enemy_Position_X] = 0;
			Map[Enemy_Position_Y][Enemy_Position_X] = ' ';
			Enemy_Position_Y--;
			Map[Enemy_Position_Y][Enemy_Position_X] = Sign;
			counter--;
		}
		else if (copyMapInt[Enemy_Position_Y + 1][Enemy_Position_X] == counter)
		{
			copyMapInt[Enemy_Position_Y][Enemy_Position_X] = 0;
			Map[Enemy_Position_Y][Enemy_Position_X] = ' ';
			Enemy_Position_Y++;
			Map[Enemy_Position_Y][Enemy_Position_X] = Sign;
			counter--;
		}
		else if (copyMapInt[Enemy_Position_Y][Enemy_Position_X - 1] == counter)
		{
			copyMapInt[Enemy_Position_Y][Enemy_Position_X] = 0;
			Map[Enemy_Position_Y][Enemy_Position_X] = ' ';
			Enemy_Position_X--;
			Map[Enemy_Position_Y][Enemy_Position_X] = Sign;
			counter--;
		}
		else if (copyMapInt[Enemy_Position_Y][Enemy_Position_X + 1] == counter)
		{
			copyMapInt[Enemy_Position_Y][Enemy_Position_X] = 0;
			Map[Enemy_Position_Y][Enemy_Position_X] = ' ';
			Enemy_Position_X++;
			Map[Enemy_Position_Y][Enemy_Position_X] = Sign;
			counter--;
		}
		else
		{
			CopingMap(copyMapInt, Map);
			counter = 1;
			copyMapInt[Enemy_End_Move_Y][Enemy_End_Move_X] = 1;
			BuildingShortestPath(Enemy_Position_Y, Enemy_Position_X, counter, copyMapInt);
		}

		/*for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				cout << copyMapInt[i][j];
			}
			cout << endl;
		}*/
	}
}

//������� ��������� ���� �� ����� � ������� ���������, ���������� ��� ���������� � ������ ���� ����
bool Enemy::CheckPlayerPosition(int& Enemy_Position_Y, int& Enemy_Position_X, char Map[y][x])
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
				else if (j < Enemy_Position_X)
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




//����������� ����� � ������������� ������
void Enemy::CopingMap(int copyMapInt[y][x], char Map[y][x])
{
	for (int i = 0; i < y; i++) // <= 17
	{
		for (int j = 0; j < x; j++) // <= 36
		{
			if (Map[i][j] == 1)
			{
				copyMapInt[i][j] = 0;
			}
			else if (Map[i][j] == 2)
			{
				copyMapInt[i][j] = -2;
			}
			else if (Map[i][j] != ' ')
			{
				copyMapInt[i][j] = -1;
			}
			else
			{
				copyMapInt[i][j] = 0;
			}
		}
	}
}

//���������� �����
void Enemy::UpdateCopingMap(int copyMapInt[y][x], char Map[y][x], const Player& P)
{
	int TempMap[y][x];
	CopingMap(TempMap, Map);
	int CoordinateTemp[12][3];
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
				copyMapInt[P.Player_Position_Y][P.Player_Position_X] = -2;
			}
		}
	}

	BuildingShortestPath(Enemy_Position_Y, Enemy_Position_X, counter, copyMapInt);
}


Enemy::~Enemy()
{

}


// Player block

//�������� ������, ���������� ���� ���� ������ �( ������������ ��� ���������� ����
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
		cout << "Quit the game?(y/n)\n";
		char a;
		cin >> a;
		if (a == 'y')
		{
			state = false;
			break;
		}
		else
		{
			break;
		}
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
	cout << "Select character: \n";
	cout << "1 - Mage\n";
	cout << "2 - Warrior\n";
	cout << "3 - Archer\n";
	int a;
	cin >> a;
	switch (a)
	{
	case 1:
		Health = 100;
		Arnmor = 1;
		Gold = 25;
		break;
	case 2:
		Health = 100;
		Arnmor = 5;
		Gold = 10;
		break;
	case 3:
		Health = 130;
		Arnmor = 1;
		Gold = 10;
		break;
	default:
		break;
	}
}

Player::Player()
{
	
}

Player::~Player()
{

}
