#include "Player.h"
#include "Enemy.h"
#include "Source.h"

class Enemy;

//движение игрока, возвращает ложь если нажата ќ( используетс€ дл€ завершени€ игры
bool Player::Player_Move(bool state, char Map[y][x], vector<Enemy*> ListPtr)
{
	int counter = 0;
	switch (_getch())
	{
	case 'w':
		if (Map[PlayerPositionY - 1][PlayerPositionX] == ' ')
		{
			this->Sign = 30;
			Map[PlayerPositionY][PlayerPositionX] = ' ';
			PlayerPositionY--;
			Map[PlayerPositionY][PlayerPositionX] = Sign;
		}
		break;
	case 's':
		if (Map[PlayerPositionY + 1][PlayerPositionX] == ' ')
		{
			this->Sign = 31;
			Map[PlayerPositionY][PlayerPositionX] = ' ';
			PlayerPositionY++;
			Map[PlayerPositionY][PlayerPositionX] = Sign;
		}
		break;
	case 'd':
		if (Map[PlayerPositionY][PlayerPositionX + 1] == ' ')
		{
			this->Sign = 16;
			Map[PlayerPositionY][PlayerPositionX] = ' ';
			PlayerPositionX++;
			Map[PlayerPositionY][PlayerPositionX] = Sign;
		}
		break;
	case 'a':
		if (Map[PlayerPositionY][PlayerPositionX - 1] == ' ')
		{
			this->Sign = 17;
			Map[PlayerPositionY][PlayerPositionX] = ' ';
			PlayerPositionX--;
			Map[PlayerPositionY][PlayerPositionX] = Sign;
		}
		break;
	case 'q':
			if (this->Temp != nullptr) this->Temp->Sign = 1;
			Select_Enemy(counter, ListPtr);
			if (counter == ListPtr.size()) { counter = 0;}
		break;
	case 'e':
		if (this->Temp != nullptr)
		{
			Set_Damage_on_Enemy(Map);
			if (this->Temp->Health <= 0)
			{
				this->Temp->~Enemy();

				this->Temp = nullptr;
			}
		}
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

void Player::Set_Damage_on_Enemy(char Map[y][x])
{
	switch (Archetype)
	{
	case 1: //Mage
		for (int i = PlayerPositionY - 3; i < PlayerPositionY + 3; i++)
		{
			for (int j = PlayerPositionX - 3; j < PlayerPositionX + 3; j++)
			{
				if (this->Temp->EnemyPositionY == i && this->Temp->EnemyPositionX == j)
				{
					if (i == PlayerPositionY - 3 || i == PlayerPositionY + 3
						|| j == PlayerPositionX - 3 || j == PlayerPositionX + 3)
					{
						this->Temp->Health = this->Temp->Health - ((this->Damage / this->Temp->Armor) * 2);
						this->EnemyHealth = this->Temp->Health;
						break;
					}
					else if (i == PlayerPositionY - 2 || i == PlayerPositionY + 2
						|| j == PlayerPositionX - 2 || j == PlayerPositionX + 2)
					{
						this->Temp->Health = this->Temp->Health - (this->Damage / this->Temp->Armor);
						this->EnemyHealth = this->Temp->Health;
						break;
					}
					else
					{
						srand(time(NULL));
						int a = rand() % 100 + 1;
						if (a >= 99) {this->Temp->Health = 0;}
						else { this->Temp->Health -= 1; }
						this->EnemyHealth = this->Temp->Health;
						break;
					}
				}
			}
		}
		break;
	case 2: //Warrior
		for (int i = PlayerPositionY - 1; i < PlayerPositionY + 1; i++)
		{
			for (int j = PlayerPositionX - 1; j < PlayerPositionX + 1; j++)
			{
				this->Temp->Health = this->Temp->Health - ((this->Damage / this->Temp->Armor) * 2);
				this->EnemyHealth = this->Temp->Health;
				break;
			}
		}
		break;
	case 3: //Archer
		for (int i = PlayerPositionY - 3; i < PlayerPositionY + 3; i++)
		{
			for (int j = PlayerPositionX - 3; j < PlayerPositionX + 3; j++)
			{
				if (i == PlayerPositionY - 3 || i == PlayerPositionY + 3
					|| j == PlayerPositionX - 3 || j == PlayerPositionX + 3)
				{
					this->EnemyHealth = this->Temp->Health - (this->Damage / this->Temp->Armor); 
					break;
				}
				else if (i == PlayerPositionY - 2 || i == PlayerPositionY + 2
					|| j == PlayerPositionX - 2 || j == PlayerPositionX + 2)
				{
					this->Temp->Health -= this->Temp->Health;
					this->EnemyHealth = this->Temp->Health;
					break;
				}
				else
				{
					this->Temp->Health = this->Temp->Health - ((this->Damage / this->Temp->Armor) * 2);
					this->EnemyHealth = this->Temp->Health;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

void Player::Select_Enemy(int& counter, vector<Enemy*> ListEnemy)
{
	while (counter < ListEnemy.size())
	{
		for (int i = PlayerPositionY - 3; i < PlayerPositionY + 3; i++)
		{
			for (int j = PlayerPositionX - 3; j < PlayerPositionX + 3; j++)
			{
				if (j == ListEnemy[counter]->EnemyPositionX && i == ListEnemy[counter]->EnemyPositionY && this->Temp != ListEnemy[counter])
				{
					ListEnemy[counter]->Sign = 2;
					this->Temp = ListEnemy[counter];
					this->EnemyHealth = ListEnemy[counter]->Health;
					this->EnemyName = ListEnemy[counter]->Name;
					return;
				}
			}
		}
		counter++;
	}
}

Player::Player(char Map[y][x])
{
	srand(time(NULL));
	bool flag = false;

	PlayerPositionX = rand() % 49 + 1;
	PlayerPositionY = rand() % 24 + 1;
	while (!flag)
	{
		if (Map[PlayerPositionY][PlayerPositionX] == ' ')
		{
			Map[PlayerPositionY][PlayerPositionX] = Sign;
			flag = true;
			break;
		}
		PlayerPositionX = rand() % 49 + 1;
		PlayerPositionY = rand() % 24 + 1;
	}
	cout << "Select character: \n";
	cout << "1 - Mage\n";
	cout << "2 - Warrior\n";
	cout << "3 - Archer\n";
	cin >> Archetype;
	switch (Archetype)
	{
	case 1: //Mage
		Health = 100;
		Armor = 1;
		Gold = 25;
		Damage = 3;
		break;
	case 2: //Warrior
		Health = 100;
		Armor = 5;
		Gold = 10;
		Damage = 5;
		break;
	case 3: //Archer
		Health = 130;
		Armor = 1;
		Gold = 10;
		Damage = 4;
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
