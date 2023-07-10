#pragma once
#include "Source.h"

class Weapon
{
public:
	virtual int Get_Damage() = 0;
	virtual int Get_Weight() = 0;

};

class SingleHandedSword : public Weapon
{
public:
	inline int Get_Damage() override	{ return Damage; }
	inline int Get_Weight() override { return Weight; }

private:
	int Damage, Weight;
	string Title;
};

class DoubleEdgedSword : public Weapon
{
public:
	inline int Get_Damage() override { return Damage; }
	inline int Get_Weight() override { return Weight; }
	DoubleEdgedSword(int D, int W, string T) :
		Damage(D), Weight(W), Title(T) {}
	~DoubleEdgedSword();


private:
	int Damage, Weight;
	string Title;
};

class Staff : public Weapon
{
public:
	inline int Get_Damage() override { return Damage; }
	inline int Get_Weight() override { return Weight; }
	Staff(int D, int W, string T) :
		Damage(D), Weight(W), Title(T) {}
	~Staff();

private:
	int Damage, Weight;
	string Title;
};

class Bow : public Weapon
{
public:
	inline int Get_Damage() override { return Damage; }
	inline int Get_Weight() override { return Weight; }
	Bow(int D, int W, string T) :
		Damage(D), Weight(W), Title(T) {}
	~Bow();


private:
	int Damage, Weight;
	string Title;
};