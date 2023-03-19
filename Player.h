#pragma once
#include "Source.h"


class Player
{
public:
	Player();
	Player(char Map[y][x]);
	~Player();
	bool PlayerMove(bool state, char Map[y][x]);
	void EnemyDamage(char Map[y][x]);

	int Health, Arnmor, Gold;
	int Player_Position_X;
	int Player_Position_Y;

private:
	const char Sign = 2;
	int Damage;
	int Archetype;

};