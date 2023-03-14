#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Header.h"
#include <ctime>
using namespace std;


void main()
{
	char Map[y][x]{ '\0' };

	RenderMap(Map);

	Player P(Map);

	Enemy E(Map);


	output(Map, P.Health, P.Arnmor, P.Gold);
	bool state = true;

	while (P.PlayerMove(state, Map))
	{
		do {
			output(Map, P.Health, P.Arnmor, P.Gold);
			E.EnemyAI_Move(Map, P);
			Sleep(400);
			system("cls");
		} while (!_kbhit());
		

	}
	
	/*char a = 0;

	for (int i = 0; i < 256; i++)
	{
		cout << a << " - symbol #" << i << endl;
		a++;
	}*/
}