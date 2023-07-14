#include "Player.h"
#include "Enemy.h"
#include "Source.h"
#include "Items.h"


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
			if (this->pTempEnemy != nullptr) this->pTempEnemy->Sign = 1;
			Select_Enemy(counter, ListPtr);
			if (counter == ListPtr.size()) { counter = 0;}
		break;
	case 'e':
		if (this->pTempEnemy != nullptr)
		{
			Set_Damage_on_Enemy(Map);
			if (this->pTempEnemy->Health <= 0)
			{
				this->pTempEnemy->~Enemy();

				this->pTempEnemy = nullptr;
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
	case 3: //Mage
		for (int i = PlayerPositionY - Archetype; i < PlayerPositionY + Archetype; i++)
		{
			for (int j = PlayerPositionX - Archetype; j < PlayerPositionX + Archetype; j++)
			{
				if (this->pTempEnemy->EnemyPositionY == i && this->pTempEnemy->EnemyPositionX == j)
				{
					if (i == PlayerPositionY - Archetype || i == PlayerPositionY + Archetype
						|| j == PlayerPositionX - Archetype || j == PlayerPositionX + Archetype)
					{
						this->pTempEnemy->Health = this->pTempEnemy->Health - ((this->Damage / this->pTempEnemy->Armor) * 2);
						this->EnemyHealth = this->pTempEnemy->Health;
						break;
					}
					else if (i == PlayerPositionY - (Archetype - 1) || i == PlayerPositionY + (Archetype - 1)
						|| j == PlayerPositionX - (Archetype - 1) || j == PlayerPositionX + (Archetype - 1))
					{
						this->pTempEnemy->Health = this->pTempEnemy->Health - (this->Damage / this->pTempEnemy->Armor);
						this->EnemyHealth = this->pTempEnemy->Health;
						break;
					}
					else
					{
						srand(time(NULL));
						int a = rand() % 100 + 1;
						if (a >= 99) {this->pTempEnemy->Health = 0;}
						else { this->pTempEnemy->Health -= 1; }
						this->EnemyHealth = this->pTempEnemy->Health;
						break;
					}
				}
			}
		}
		break;
	case 2: //Warrior
		for (int i = PlayerPositionY - Archetype; i < PlayerPositionY + Archetype; i++)
		{
			for (int j = PlayerPositionX - Archetype; j < PlayerPositionX + Archetype; j++)
			{
				this->pTempEnemy->Health = this->pTempEnemy->Health - ((this->Damage / this->pTempEnemy->Armor) * 2);
				this->EnemyHealth = this->pTempEnemy->Health;
				break;
			}
		}
		break;
	case 6: //Archer
		for (int i = PlayerPositionY - Archetype; i < PlayerPositionY + 3; i++)
		{
			for (int j = PlayerPositionX - Archetype; j < PlayerPositionX + Archetype; j++)
			{
				if (i == PlayerPositionY - Archetype || i == PlayerPositionY + Archetype
					|| j == PlayerPositionX - Archetype || j == PlayerPositionX + Archetype)
				{
					this->EnemyHealth = this->pTempEnemy->Health - (this->Damage / this->pTempEnemy->Armor);
					break;
				}
				else if (i == PlayerPositionY - (Archetype / 2) || i == PlayerPositionY + (Archetype / 2)
					|| j == PlayerPositionX - (Archetype / 2) || j == PlayerPositionX + (Archetype / 2))
				{
					this->pTempEnemy->Health -= this->pTempEnemy->Health;
					this->EnemyHealth = this->pTempEnemy->Health;
					break;
				}
				else
				{
					this->pTempEnemy->Health = this->pTempEnemy->Health - ((this->Damage / this->pTempEnemy->Armor) * 2);
					this->EnemyHealth = this->pTempEnemy->Health;
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
		for (int i = PlayerPositionY - Archetype; i < PlayerPositionY + Archetype; i++)
		{
			for (int j = PlayerPositionX - Archetype; j < PlayerPositionX + Archetype; j++)
			{
				if (j == ListEnemy[counter]->EnemyPositionX && i == ListEnemy[counter]->EnemyPositionY && this->pTempEnemy != ListEnemy[counter])
				{
					ListEnemy[counter]->Sign = 2;
					this->pTempEnemy = ListEnemy[counter];
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

	Inventory Invent(5);
	Items::Item Stuff("Magic Stuff", 1, 4);
	Invent.Set_Item_In_Inventory(Stuff);

	cin >> Archetype;
	switch (Archetype)
	{
	case 1: //Mage
		Health = 100;
		Armor = 1;
		Damage = 1;
		Archetype = 3;
		break;
	case 2: //Warrior
		Health = 100;
		Armor = 5;
		Damage = 1;
		break;
	case 3: //Archer
		Health = 130;
		Armor = 1;
		Damage = 1;
		Archetype = 6;
		break;
	default:
		break;
	}
}


Player::Inventory::Inventory(int Size)
{
	Slot = new SlotInventory[Size];
	Wallet = 25;
}

void Player::Inventory::Set_Item_In_Inventory(Items::Item &item)
{
	this->Slot[0].Title = item.Title;
	this->Slot[0].ID = item.ID;
	this->Slot[0].Characteristic = item.Characteristic;
}

Player::Inventory::~Inventory()
{
	delete[] Slot;
}

Player::Player()
{

}

Player::~Player()
{

}

Player::Inventory::SlotInventory::SlotInventory()
{
}
