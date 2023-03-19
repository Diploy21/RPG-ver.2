#include "Source.h"

using namespace std;


// ожидание
void Sleep1(unsigned a)
{
	this_thread::sleep_for(chrono::seconds(a));
}

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

void output(char Map[y][x], int H, int A, int G)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (i == 0 && j == x - 1)
			{
				cout << Map[i][j] << "\t Health - " << H;
			}
			else if (i == 1 && j == x - 1)
			{
				cout << Map[i][j] << "\t Armor  - " << A;
			}
			else if (i == 2 && j == x - 1)
			{
				cout << Map[i][j] << "\t Gold   - " << G;
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
