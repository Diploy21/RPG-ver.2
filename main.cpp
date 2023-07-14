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

		
		/*vector<Enemy*> ListPtrOnEnemy;

		Enemy Sk("Skillet", Map, P);
		ListPtrOnEnemy.push_back(&Sk);

		Enemy FlSku("Fly Skull", Map, P);
		ListPtrOnEnemy.push_back(&FlSku);

		while (P.Player_Move(state, Map, ListPtrOnEnemy) && P.Get_Player_Health())
		{
			do {
				output(Map, P);
				if (Sk.Get_Enemy_Health() > 0) Sk.EnemyAI_Move(Map, P);
				if (FlSku.Get_Enemy_Health() > 0) FlSku.EnemyAI_Move(Map, P);
				Sleep(400);
				system("cls");
			} while (!_kbhit());
		}*/
	}
		
}