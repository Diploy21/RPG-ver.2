#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Header.h"
using namespace std;


void main()
{
	const int X = 50;
	const int Y = 25;
	char Map[Y][X]{ '\0' };

	RenderMap(Map, Y);

	Player P(Map, Y);

	Enemy E(Map, Y);


	output(Map, Y, P.Health, P.Arnmor, P.Gold);
	bool state = true;

	while (true)//P.PlayerMove(state, P, Map, Y))
	{
		//do {
			output(Map, Y, P.Health, P.Arnmor, P.Gold);
			Sleep(240);
			E.EnemyAI_Move(Map, Y);
			
			system("cls");
		//} while (!_kbhit());
		

	}
	
	char a = 0;

	for (int i = 0; i < 256; i++)
	{
		cout << a << " - symbol #" << i << endl;
		a++;
	}
}