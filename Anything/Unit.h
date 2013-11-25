#ifndef _UNIT_H
#define _UNIT_H

#include <string>
#include <SFML/Graphics.hpp>

class Unit
{
	private:

	public:
		//constant
		int ID;
		std::string name, corpseImageName;
		std::vector<std::string> imageName, gatherList;
		int maxHealth, maxThirst, maxHunger;
		bool gatherable, canSwim;
		
		//variable
		int direction;
		int health, thirst, hunger;
		int hostility, attack;
		int inventorySizeX, inventorySizeY;
		int actionBarSizeX, actionBarSizeY;
		std::vector<std::vector<int>> inventory;
		std::vector<std::vector<int>> actionBar;

		Unit(void);
		~Unit(void);
		Unit(int ID, std::string name, std::vector<std::string> imageName, std::string corpseImageName, int maxHealth, int maxThirst, int maxHunger, int health, int thirst, int hunger, int hostility, int attack, bool gatherable, bool canSwim);
		void changeDirection(int direction);
		void initializeInventory();
};

#endif