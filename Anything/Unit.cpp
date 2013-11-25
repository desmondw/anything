#include "Unit.h"

Unit::Unit(void)
{
}

Unit::~Unit(void)
{
}

Unit::Unit(int ID, std::string name, std::vector<std::string> imageName, std::string corpseImageName, int maxHealth, int maxThirst, int maxHunger, int health, int thirst, int hunger, int hostility, int attack, bool gatherable, bool canSwim)
{
	this->ID = ID;
	this->name = name;
	this->imageName = imageName;
	this->corpseImageName = corpseImageName;
	this->maxHealth = maxHealth;
	this->maxThirst = maxThirst;
	this->maxHunger = maxHunger;
	this->health = health;
	this->thirst = thirst;
	this->hunger = hunger;
	this->attack = attack;
	this->hostility = hostility;
	this->gatherable = gatherable;
	this->canSwim = canSwim;

	direction = 0;
	inventorySizeX = 7;
	inventorySizeY = 3;
	actionBarSizeX = 1;
	actionBarSizeY = 3;
	inventory = std::vector<std::vector<int>>(inventorySizeX, std::vector<int>(inventorySizeY));
	actionBar = std::vector<std::vector<int>>(actionBarSizeX, std::vector<int>(actionBarSizeY));
	initializeInventory();
}

void Unit::changeDirection(int direction)
{
	this->direction = direction;
}

void Unit::initializeInventory()
{
	for (int i=0; i<inventory.size(); i++)
	{
		for (int j=0; j<inventory[i].size(); j++)
		{
			inventory[i][j] = -1;
		}
	}
	
	for (int i=0; i<actionBar.size(); i++)
	{
		for (int j=0; j<actionBar[i].size(); j++)
		{
			actionBar[i][j] = -1;
		}
	}


	//TODO: remove this test case
	inventory[0][2] = 2;
	inventory[5][1] = 2;
	actionBar[0][1] = 2;
}