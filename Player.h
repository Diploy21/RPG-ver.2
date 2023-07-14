#pragma once
#include "Source.h"
#include "Items.h"


class Player
{
	friend void output(char Map[y][x], Player &P);
	friend class Enemy;
	friend class Items::Item;

public:

	Player();
	Player(char Map[y][x]);
	~Player();
	bool Player_Move(bool state, char Map[y][x], vector<Enemy*> ListPtr);
	void Set_Damage_on_Enemy(char Map[y][x]);
	inline int Get_Player_Health() { return this->Health; }
	inline void Healing_Player(int AddHealth) { this->Health = this->Health + AddHealth; }
	void Select_Enemy(int& counter, vector<Enemy*> ListEnemy);
	inline int Get_Gold() { return Inventory::Get_Money_on_Wallet(); }

private:
	int Health, Armor, Damage, Archetype;
	int PlayerPositionX, PlayerPositionY;
	char Sign = 30;
	Enemy* pTempEnemy = nullptr;
	string EnemyName;
	int EnemyHealth;

	class Hands
	{
	public:
		void Pick_Item_On_Hand();
	protected:

		class Hand
		{
		public:
			
		};
		Hand Left;
		Hand Right;
	};

	class Inventory
	{
		friend class Items::Item;

	public:
		Inventory(int Size);
		Item Get_Item_From_Inventory(int index);
		void Set_Item_In_Inventory(Items::Item &item);
		void Get_All_Slots();
		inline static int Get_Money_on_Wallet() { return Wallet; }

	protected:

		class SlotInventory
		{
			friend class Inventory;
			friend class Items::Item;

		public:
			SlotInventory();
			string Title;
			int ID;
			int Characteristic;
		};

		int Size;
		static int Wallet;
		SlotInventory* Slot;
		
	};

};

