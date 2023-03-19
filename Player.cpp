#include "Player.h"
#include "Source.h"
#include "Enemy.h"


//движение игрока, возвращает ложь если нажата ќ( используетс€ дл€ завершени€ игры
bool Player::PlayerMove(bool state, char Map[y][x])
{
	switch (_getch())
	{
	case 'w':
		if (Map[Player_Position_Y - 1][Player_Position_X] == ' ')
		{
			Map[Player_Position_Y][Player_Position_X] = ' ';
			Player_Position_Y--;
			Map[Player_Position_Y][Player_Position_X] = Sign;
		}
		break;
	case 's':
		if (Map[Player_Position_Y + 1][Player_Position_X] == ' ')
		{
			Map[Player_Position_Y][Player_Position_X] = ' ';
			Player_Position_Y++;
			Map[Player_Position_Y][Player_Position_X] = Sign;
		}
		break;
	case 'd':
		if (Map[Player_Position_Y][Player_Position_X + 1] == ' ')
		{
			Map[Player_Position_Y][Player_Position_X] = ' ';
			Player_Position_X++;
			Map[Player_Position_Y][Player_Position_X] = Sign;
		}
		break;
	case 'a':
		if (Map[Player_Position_Y][Player_Position_X - 1] == ' ')
		{
			Map[Player_Position_Y][Player_Position_X] = ' ';
			Player_Position_X--;
			Map[Player_Position_Y][Player_Position_X] = Sign;
		}
		break;
	case 'e':
		EnemyDamage();
		break;
	case 'o':
		cout << "Quit the game?(y/n)\n";
		char a;
		cin >> a;
		if (a == 'y')
		{
			state = false;
			break;
		}
		else
		{
			break;
		}
	default:
		break;
	}
	return state;
}

void Player::EnemyDamage(char Map[y][x])
{
	switch(Archetype)
	{
	case 1:
		for (int i = Player_Position_Y  - 3; i < Player_Position_Y + 3; i++)
		{
			for (int j = Player_Position_X - 3; j < Player_Position_X + 3; j++)
			{
				if(Map[i][j])
			}
		}
		break;
	case 2:
		for (int i = Player_Position_Y - 1; i < Player_Position_Y + 1; i++)
		{
			for (int j = Player_Position_X - 1; j < Player_Position_X + 1; j++)
			{
				if ()
			}
		}
		break;
	case 3:
		for (int i = Player_Position_Y - 3; i < Player_Position_Y + 3; i++)
		{
			for (int j = Player_Position_X - 3; j < Player_Position_X + 3; j++)
			{
				if ()
			}
		}
		break;
	default:
		break;
	}
}

Player::Player(char Map[y][x])
{
	srand(time(NULL));
	bool flag = false;

	Player_Position_X = rand() % 49 + 1;
	Player_Position_Y = rand() % 24 + 1;
	while (!flag)
	{
		if (Map[Player_Position_Y][Player_Position_X] == ' ')
		{
			Map[Player_Position_Y][Player_Position_X] = Sign;
			flag = true;
			break;
		}
		Player_Position_X = rand() % 49 + 1;
		Player_Position_Y = rand() % 24 + 1;
	}
	cout << "Select character: \n";
	cout << "1 - Mage\n";
	cout << "2 - Warrior\n";
	cout << "3 - Archer\n";
	cin >> Archetype;
	switch (Archetype)
	{
	case 1:
		Health = 100;
		Arnmor = 1;
		Gold = 25;
		break;
	case 2:
		Health = 100;
		Arnmor = 5;
		Gold = 10;
		break;
	case 3:
		Health = 130;
		Arnmor = 1;
		Gold = 10;
		break;
	default:
		break;
	}
}

Player::Player()
{

}

Player::~Player()
{

}
