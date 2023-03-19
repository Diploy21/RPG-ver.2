#include "Source.h"
#include "Player.h"
#include "Enemy.h"


void main()
{
	char Map[y][x]{ ' ' };

	bool state = true;

	if (Menu(state))
	{
		RenderMap(Map);

		Player P(Map);

		Enemy E(Map);
		Enemy R(Map);

		while (P.PlayerMove(state, Map) && P.Health != 0)
		{
			do {
				output(Map, P.Health, P.Arnmor, P.Gold);
				E.EnemyAI_Move(Map, P);
				R.EnemyAI_Move(Map, P);
				Sleep(400);
				system("cls");
			} while (!_kbhit());
		}
	}
	
	/*char a = 0;

	for (int i = 0; i < 256; i++)
	{
		cout << a << " - symbol #" << i << endl;
		a++;
	}*/
}