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
			Sleep(400);
			E.EnemyAI_Move(Map);
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



//bool check(int Map[y][x], int EY, int EX, int d)
//{
//	bool state = false;
//
//	for (int i = 1; i < y - 1; i++)
//	{
//		for (int j = 1; j < x - 1; j++)
//		{
//			if (Map[i][j] == 0)
//			{
//				state = true;
//			}
//		}
//	}
//	if (Map[EY][EX] == d)
//	{
//		state = false;
//	}
//	return state;
//}
//
//
//void main()
//{
//	srand(time(NULL));
//	char Map[y][x];
//
//	for (int i = 0; i < y; i++)
//	{
//		for (int j = 0; j < x; j++)
//		{
//			if (i == 0 || j == 0 || i == y - 1 || j == x - 1)
//			{
//				Map[i][j] = '#';
//			}
//			else
//			{
//				Map[i][j] = '.';
//			}
//		}
//	}
//
//	char Sign = 'e';
//	int SY = rand() % (y - 1) + 1, SX = rand() % (x - 1) + 1;
//	Map[SY][SX] = Sign;
//
//	int EndX = rand() % (x - 1) + 1, EndY = rand() % (y - 1) + 1;
//	Map[EndY][EndX] = 'o';
//
//	int Map1[y][x];
//
//	int EX, EY, Sy, Sx;
//
//	for (int i = 0; i < y; i++) // <= 17
//	{
//		for (int j = 0; j < x; j++) // <= 36
//		{
//			if (Map[i][j] == 'e' )
//			{
//				Sy = i;
//				Sx = j;
//				Map1[i][j] = 0;
//			}
//			else if (Map[i][j] == 'o')
//			{
//				EY = i;
//				EX = j;
//				Map1[i][j] = 0;
//			}
//			else if (Map[i][j] != '.')
//			{
//				Map1[i][j] = -1;
//			}
//			else
//			{
//				Map1[i][j] = 0;
//			}
//		}
//	}
//	
//	int d = 1;
//	Map1[EY][EX] = d;
//	while (check(Map1, Sy, Sx, d))
//	{
//		for (int i = 1; i < y - 1; i++)
//		{
//			for (int j = 1; j < x - 1; j++)
//			{
//				if (Map1[i][j] == d)
//				{
//					if (Map1[i - 1][j] == 0)
//					{
//						Map1[i - 1][j] = d + 1;
//					}
//					if (Map1[i + 1][j] == 0)
//					{
//						Map1[i + 1][j] = d + 1;
//					}
//					if (Map1[i][j - 1] == 0)
//					{
//						Map1[i][j - 1] = d + 1;
//					}
//					if (Map1[i][j + 1] == 0)
//					{
//						Map1[i][j + 1] = d + 1;
//					}
//				}
//			}
//		}
//		d++;
//	}
//	d--;
//	while (check(Map1, EY, EX, d))
//	{
//		if (Map1[Sy - 1][Sx] == d)
//		{
//			Map1[Sy][Sx] = 0;
//			Map[Sy][Sx] = '0';
//			Sy--;
//			Map[Sy][Sx] = 'E';
//			d--;
//		}
//		if (Map1[Sy + 1][Sx] == d)
//		{
//			Map1[Sy][Sx] = 0;
//			Map[Sy][Sx] = '0';
//			Sy++;
//			Map[Sy][Sx] = 'E';
//			d--;
//		}
//		if (Map1[Sy][Sx - 1] == d)
//		{
//			Map1[Sy][Sx] = 0;
//			Map[Sy][Sx] = '0';
//			Sx--;
//			Map[Sy][Sx] = 'E';
//			d--;
//		}
//		if (Map1[Sy][Sx + 1] == d)
//		{
//			Map1[Sy][Sx] = 0;
//			Map[Sy][Sx] = '0';
//			Sx++;
//			Map[Sy][Sx] = 'E';
//			d--;
//		}
//	}
//
//
//	for (int i = 0; i < y; i++)
//	{
//		for (int j = 0; j < x; j++)
//		{
//			cout << Map[i][j];
//		}
//		cout << endl;
//	}
//
//	for (int i = 0; i < y; i++)
//	{
//		for (int j = 0; j < x; j++)
//		{
//			if (Map1[i][j] > 0)
//			{
//				Map1[i][j] = 1;
//			}
//			cout << Map1[i][j];
//		}
//		cout << endl;
//	}
//}
