#pragma once
#include "Source.h"

class Player;

class Enemy
{
	friend class Player;
	friend void output(char Map[y][x], Player& P);

public:
	static int ID;

	Enemy(string SetName, char Map[y][x], Player &P);
	~Enemy();

	void EnemyAI_Move(char Map[y][x], Player& P);
	void Coping_Map(int copy_Map_Int[y][x], char Map[y][x], Player& P);
	void Update_Coping_Map(int copy_Map_Int[y][x], char Map[y][x], Player& P);
	void Enemy_Move(int& EnemyPositionY, int& EnemyPositionX, int copy_Map_Int[y][x], char Map[y][x], Player& P);
	void Building_Shortest_Path(int EnemyPositionY, int EnemyPositionX, int& counter, int copy_Map_Int[y][x]);
	bool Path_Finder_Check(int Map[y][x], int EnemyEndMoveY, int EnemyEndMoveX, int d);
	bool Check_Player_Position(int& EnemyEndMoveY, int& EnemyEndMoveX, char Map[y][x], Player& P);
	inline int Get_Enemy_Health() { return this->Health; }
	inline string Get_Enemy_Name() { return this->Name; }

private:
	int Health, Armor, Damage;
	char Sign = 1;
	string Name;
	int EnemyPositionX, EnemyPositionY, EnemyEndMoveX, EnemyEndMoveY;
	int counter;
	int copy_Map_Int[y][x];

};
