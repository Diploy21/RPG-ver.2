#pragma once
#include "Source.h"
#include"Player.h"

using namespace std;

enum class CharacterID{Weapon = 'W', Armor = 'A', HealthPot= 'H'};

class Item
{
	friend class Player::Inventory;
	using enum CharacterID;
public:
	inline Item Get_Item_Type() { return *this; }
	Item(string Ttl, enum CharacterID id, int Charact);
	Item();
	~Item();

private:
	string Title;
	char ItemID;
	int Characteristic;
};
