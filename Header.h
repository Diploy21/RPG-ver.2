#pragma once

using namespace std;

#define x 50
#define y 25

class Player
{
public:
	Player();
	Player(char Map[y][x]);
	~Player();
	bool PlayerMove(bool state, char Map[y][x]);
	int Health, Arnmor, Gold;
	int Player_Position_X;
	int Player_Position_Y;

private:
	const char Sign = 2;
	int Damage;

};

class Enemy
{
public:
	Enemy(char Map[y][x]);
	~Enemy();
	
	void EnemyAI_Move(char Map[y][x], Player& P);

private:
	void CopingMap(int copyMapInt[y][x], char Map[y][x]);
	void UpdateCopingMap(int copyMapInt[y][x], char Map[y][x], const Player& P);
	void ClearCopingMap(int copyMapInt[y][x]);

	void EnemyMove(int& Enemy_Position_Y, int& Enemy_Position_X, int copyMapInt[y][x], char Map[y][x]);

	void BuildingShortestPath(int Enemy_Position_Y, int Enemy_Position_X, int& counter, int copyMapInt[y][x]);

	bool PathFinderCheck(int Map[y][x], int Enemy_End_Move_Y, int Enemy_End_Move_X, int d);

	bool CheckPlayerPosition(int& Enemy_End_Move_Y, int& Enemy_End_Move_X, char Map[y][x]);

	const char Sign = 1;
	int Enemy_Position_X;
	int Enemy_Position_Y;
	int Health, Arnmor, Damage, Gold;
	int Enemy_End_Move_X, Enemy_End_Move_Y;
	int counter;
	int copyMapInt[y][x];

};

void RenderMap(char Map[y][x]);
void output(char Map[y][x], int H = 0, int A = 0, int G = 0);
void Sleep();

