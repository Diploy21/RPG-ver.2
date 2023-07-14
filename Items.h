#pragma once
#include "Source.h"

namespace Items
{
	class Item
	{
	public:
		inline Item Get_Item_Type() { return *this; }
		Item(string Ttl, int id, int Charact);
		~Item();

	private:
		string Title;
		int ID;
		int Characteristic;
	};


	/*class MainWeapon : public Item
	{

	};

	class SecWeapon : public Item
	{

	};

	class Armor : public Item
	{

	};*/


}