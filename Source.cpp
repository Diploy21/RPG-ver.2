#include "Source.h"
#include "Enemy.h"
#include "Player.h"
using namespace std;

class Player;

//Menu
bool Menu(bool state)
{
	cout << "\t\t\t\t My Game\n";
	cout << "\t\t1 - Start game.\n";
	cout << "\t\t2 - Out.\n";
	int a;
	cin >> a;

	switch(a)
	{
	case 1:
		state = true;
		break;
	case 2:
		state = false;
		break;
	default:
		break;
	}
	return state;
}

//  Map block
void RenderMap(char Map[y][x])
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (i == 0 && j == 0)
			{
				Map[i][j] = 201;
			}
			else if (i == y - 1 && j == 0)
			{
				Map[i][j] = 200;
			}
			else if (i == 0 && j == x - 1)
			{
				Map[i][j] = 187;
			}
			else if (i == y - 1 && j == x - 1)
			{
				Map[i][j] = 188;
			}
			else if (i == 0 || i == y - 1)
			{
				Map[i][j] = 205;
			}
			else if (j == 0 || j == x - 1)
			{
				Map[i][j] = 186;
			}
			else
			{
				Map[i][j] = ' ';
			}
		}
	}
}

void output(char Map[y][x], Player &P)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (i == 0 && j == x - 1)
			{
				cout << Map[i][j] << "\t Health - " << P.Health;
			}
			else if (i == 1 && j == x - 1)
			{
				cout << Map[i][j] << "\t Armor  - " << P.Armor;
			}
			else if (i == 2 && j == x - 1)
			{
				cout << Map[i][j] << "\t Gold   - " << P.Gold;
			}
			else if (i == 5 && j == x - 1)
			{
				if (P.EnemyName == " ") { cout << Map[i][j] << "\t Enemy Name - "; }
				else { cout << Map[i][j] << "\t Enemy Name - " << P.EnemyName; }
			}
			else if (i == 6 && j == x - 1)
			{
				if (P.EnemyHealth == 0) { cout << Map[i][j] << "\t Enemy Health - "; }
				else { cout << Map[i][j] << "\t Enemy Health - " << P.EnemyHealth; }
			}
			else
			{
				cout << Map[i][j];
			}
		}
		cout << endl;
	}
}


// Enemy block



// Player block
