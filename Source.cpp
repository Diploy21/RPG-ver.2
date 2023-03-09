#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include "Header.h"
using namespace std;

void RenderMap(char Map[][50], int Y)
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (i == 0 && j == 0)
			{
				Map[i][j] = 201;
			}
			else if (i == Y - 1 && j == 0)
			{
				Map[i][j] = 200;
			}
			else if (i == 0 && j == 49)
			{
				Map[i][j] = 187;
			}
			else if (i == Y - 1 && j == 49)
			{
				Map[i][j] = 188;
			}
			else if (i == 0 || i == Y - 1)
			{
				Map[i][j] = 205;
			}
			else if (j == 0 || j == 49)
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

void output(char Map[][50], int Y, int H, int A, int G)
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (i == 0 && j == 49)
			{
				cout << Map[i][j] << "\t Health - " << H;
			}
			else if (i == 1 && j == 49)
			{
				cout << Map[i][j] << "\t Armor  - " << A;
			}
			else if (i == 2 && j == 49)
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

//функция движения в заданном направлении на заданное расстояние
void Enemy::MoveState(int direc, int& dist) //private
{
	switch (direc)
	{
	case 1:
		if (Enemy_Pos_y != Enemy_Pos_y - dist)
		{
			Enemy_Pos_y--;
			dist--;
		}
		break;
	case 2:
		if (Enemy_Pos_y != Enemy_Pos_y + dist)
		{
			Enemy_Pos_y++;
			dist--;
		}
		break;
	case 3:
		if (Enemy_Pos_x != Enemy_Pos_x - dist)
		{
			Enemy_Pos_x--;
			dist--;
		}
		break;
	case 4:
		if (Enemy_Pos_x != Enemy_Pos_x + dist);
		{
			Enemy_Pos_x++;
			dist--;
		}
		break;
	default:
		break;
	}
}

//функция проверяет возможно ли движение в заданом направлении на заданное расстояние
bool Enemy::DirectionCheck(int direc, int dist, char Map[][50], int Y) //private
{
	bool state = false;
	switch (direc)
	{
	case 1:
		for (int i = Enemy_Pos_y; i != Enemy_Pos_y - dist; i--)
		{
			if (Map[i][Enemy_Pos_x] != ' ')
			{
				state = false;
				break;
			}
			else
			{
				state = true;
			}
		}
		break;
	case 2:
		for (int i = Enemy_Pos_y; i != Enemy_Pos_y + dist; i++)
		{
			if (Map[i][Enemy_Pos_x] != ' ')
			{
				state = false;
				break;
			}
			else
			{
				state = true;
			}
		}
		break;
	case 3:
		for (int i = Enemy_Pos_x; i != Enemy_Pos_y - dist; i--)
		{
			if (Map[Enemy_Pos_y][i] != ' ')
			{
				state = false;
				break;
			}
			else
			{
				state = true;
			}
		}
		break;
	case 4:
		for (int i = Enemy_Pos_x; i != Enemy_Pos_y + dist; i++)
		{
			if (Map[Enemy_Pos_y][i] != ' ')
			{
				state = false;
				break;
			}
			else
			{
				state = true;
			}
		}
		break;
	default:
		break;
	}
	return state;
}

//реализация движения
void Enemy::EnemyAI_Move(char Map[][50], int Y)
{
	srand(time(NULL));
	bool state = false;

	while (!state)
	{
		if (DirectionCheck(MoveDirection, MoveDistantion, Map, Y))
		{
			Map[Enemy_Pos_y][Enemy_Pos_x] = ' ';
			MoveState(MoveDirection, MoveDistantion);
			Map[Enemy_Pos_y][Enemy_Pos_x] = Sign;
			state = true;
		}
		else
		{
			MoveDistantion--;
			if (MoveDistantion == 0)
			{
				MoveDistantion = rand() % 4 + 1;
			}
		}
	}
	
	if (state)
	{
		MoveDirection = rand() % 4 + 1;
		MoveDistantion = rand() % 4 + 1;
	}
}

Enemy::Enemy(char Map[][50], int Y)
{
	srand(time(NULL));
	Enemy_Pos_x = rand() % 49 + 1;
	Enemy_Pos_y = rand() % 24 + 1;
	bool flag = false;
	while (!flag)
	{
		if (Map[Enemy_Pos_y][Enemy_Pos_x] == ' ')
		{
			Map[Enemy_Pos_y][Enemy_Pos_x] = Sign;
			flag = true;
			break;
		}
		Enemy_Pos_x = rand() % 49 + 1;
		Enemy_Pos_y = rand() % 24 + 1;
	}
	MoveDirection = rand() % 4 + 1;
	MoveDistantion = rand() % 4 + 1;
	Health = 100;
	Arnmor = 1;
	Gold = 10;
}

Enemy::~Enemy()
{

}

// Player block

//движение игрока, возвращает ложь если нажата О( используется для завершения игры
bool Player::PlayerMove(bool state, Player& P, char Map[][50], int Y)
{
	switch (_getch())
	{
	case 'w':
		if (Map[Player_Pos_y - 1][Player_Pos_x] == ' ')
		{
			Map[Player_Pos_y][Player_Pos_x] = ' ';
			Player_Pos_y--;
			Map[Player_Pos_y][Player_Pos_x] = Sign;
			system("cls");
			output(Map, Health, Arnmor, Gold);
		}
		else {
			system("cls");
			output(Map, Health, Arnmor, Gold);
		}
		break;
	case 's':
		if (Map[Player_Pos_y + 1][Player_Pos_x] == ' ')
		{
			Map[Player_Pos_y][Player_Pos_x] = ' ';
			Player_Pos_y++;
			Map[Player_Pos_y][Player_Pos_x] = Sign;
			system("cls");
			output(Map, Health, Arnmor, Gold);
		}
		else {
			system("cls");
			output(Map, Health, Arnmor, Gold);
		}
		break;
	case 'd':
		if (Map[Player_Pos_y][Player_Pos_x + 1] == ' ')
		{
			Map[Player_Pos_y][Player_Pos_x] = ' ';
			Player_Pos_x++;
			Map[Player_Pos_y][Player_Pos_x] = Sign;
			system("cls");
			output(Map, Health, Arnmor, Gold);
		}
		else {
			system("cls");
			output(Map, Health, Arnmor, Gold);
		}
		break;
	case 'a':
		if (Map[Player_Pos_y][Player_Pos_x - 1] == ' ')
		{
			Map[Player_Pos_y][Player_Pos_x] = ' ';
			Player_Pos_x--;
			Map[Player_Pos_y][Player_Pos_x] = Sign;
			system("cls");
			output(Map, Health, Arnmor, Gold);
		}
		else {
			system("cls");
			output(Map, Health, Arnmor, Gold);
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

Player::Player(char Map[][50], int Y)
{
	srand(time(NULL));
	bool flag = false;

	Player_Pos_x = rand() % 49 + 1;
	Player_Pos_y = rand() % 24 + 1;
	while (!flag)
	{
		if (Map[Player_Pos_y][Player_Pos_x] == ' ')
		{
			Map[Player_Pos_y][Player_Pos_x] = Sign;
			flag = true;
			break;
		}
		Player_Pos_x = rand() % 49 + 1;
		Player_Pos_y = rand() % 24 + 1;
	}
	Health = 100;
	Arnmor = 1;
	Gold = 10;
}

Player::~Player()
{

}


