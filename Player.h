#pragma once
#include "Source.h"

class Player
{
	friend void output(char Map[y][x], Player &P);
	friend class Enemy;
	friend class Weapon;

public:

	Player();
	Player(char Map[y][x]);
	~Player();
	bool Player_Move(bool state, char Map[y][x], vector<Enemy*> ListPtr);
	void Set_Damage_on_Enemy(char Map[y][x]);
	inline int Get_Player_Health() { return this->Health; }
	inline void Healing_Player(int AddHealth) { this->Health = this->Health + AddHealth; }
	void Select_Enemy(int& counter, vector<Enemy*> ListEnemy);	

private:
	int Health, Armor, Gold, Damage, Archetype;
	int PlayerPositionX, PlayerPositionY;
	char Sign = 30;
	Enemy* Temp = nullptr;
	string EnemyName;
	int EnemyHealth;

	template <typename Item>
	class Inventory
	{
	public:
		template <typename T> T Get_Item_Stat();
		void Place_Item(Item Item);
		Item Pick_Item();
		Inventory();
		Inventory& operator= (Inventory& Prev);

	protected:
		Item* SlotInventory;

	};

};


