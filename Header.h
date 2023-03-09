#pragma once

#include <string>
using namespace std;


class Player
{
public:

	Player(char Map[][50], int Y);
	~Player();
	bool PlayerMove(bool state, Player& P, char Map[][50], int Y);
	int Health, Arnmor, Gold;

private:
	const char Sign = 2;
	int Player_Pos_x;
	int Player_Pos_y;
	int Damage;
};

class Enemy
{
public:
	Enemy(char Map[][50], int Y);
	~Enemy();
	
	void EnemyAI_Move(char Map[][50], int Y);

private:
	void MoveState(int direc, int& dist);
	bool DirectionCheck(int direc, int dist, char Map[][50], int Y);

	const char Sign = 1;
	int Enemy_Pos_x;
	int Enemy_Pos_y;
	int Health, Arnmor, Damage, Gold;
	int MoveDistantion = -1;
	int MoveDirection = -1;
	bool flag = false;
};

void RenderMap(char Map[][50], int Y);
void output(char Map[][50], int Y, int H = 0, int A = 0, int G = 0);

