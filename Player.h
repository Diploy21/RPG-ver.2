#pragma once
#include "Source.h"
#include "Items.h"

#define x 50
#define y 25

using namespace std;

class SlotInventory;
//class Hand;
class Enemy;
class Item;

class Player
{
	friend void output(char Map[y][x], Player &P);
	friend class Enemy;
	friend class Item;

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

	/*class Hands
	{
	public:
		void Pick_Item_On_Hand();

	protected:
		Hand Left;
		Hand Right;
	};*/

	class Inventory
	{
		friend class Item;

	public:
		Inventory(int Size);
		~Inventory();
		Item Pick_Item_From_Inventory(int index);
		void Add_Item_In_Inventory(Item &item);
		void Get_All_Slots();
		inline static int Get_Money_on_Wallet() { return Wallet; }
		inline static void Add_Money_on_Wallet(const int Money) { Wallet += Money; }

	protected:

		int Size;
		static int Wallet;
		SlotInventory* Slot;
		
	};

};

class SlotInventory
{
	friend class Item;

public:
	SlotInventory();
	string TitleItem;
	char ID;
	int Characteristic;
};

//class Hand
//{
//public:
//	Hand();
//};