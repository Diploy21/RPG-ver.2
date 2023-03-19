#pragma once
#include "Source.h"
#include "Player.h"

class Enemy
{
public:
	Enemy(char Map[y][x]);
	~Enemy();

	void EnemyAI_Move(char Map[y][x], Player& P);
	int Health, Arnmor, Damage;

private:
	void CopingMap(int copyMapInt[y][x], char Map[y][x]);
	void UpdateCopingMap(int copyMapInt[y][x], char Map[y][x], const Player& P);
	void EnemyDamage();

	void EnemyMove(int& Enemy_Position_Y, int& Enemy_Position_X, int copyMapInt[y][x], char Map[y][x]);

	void BuildingShortestPath(int Enemy_Position_Y, int Enemy_Position_X, int& counter, int copyMapInt[y][x]);

	bool PathFinderCheck(int Map[y][x], int Enemy_End_Move_Y, int Enemy_End_Move_X, int d);

	bool CheckPlayerPosition(int& Enemy_End_Move_Y, int& Enemy_End_Move_X, char Map[y][x]);

	const char Sign = 1;
	int Enemy_Position_X;
	int Enemy_Position_Y;
	int Enemy_End_Move_X, Enemy_End_Move_Y;
	int counter;
	int copyMapInt[y][x];

};
