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

		vector<Enemy*> ListPtrOnEnemy;

		Enemy E("Skillet", Map, P);
		ListPtrOnEnemy.push_back(&E);

		Enemy R("Fly Skull", Map, P);
		ListPtrOnEnemy.push_back(&R);

		while (P.Player_Move(state, Map, ListPtrOnEnemy) && P.Get_Player_Health())
		{
			do {
				output(Map, P);
				if (E.Get_Enemy_Health() > 0) E.EnemyAI_Move(Map, P);
				if (R.Get_Enemy_Health() > 0) R.EnemyAI_Move(Map, P);
				Sleep(400);
				system("cls");
			} while (!_kbhit());
		}
	}
		
}