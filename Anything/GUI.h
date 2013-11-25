#ifndef _GUI_H
#define _GUI_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <sstream>
#include <string>
#include "GameData.h"

class GUI
{
	private:
		sf::Image inventoryImage;
		static const int MIN_RESOLUTION_X = 1024, MIN_RESOLUTION_Y = 768;

		//resources
		sf::Font font;
		std::vector<sf::Image> itemImgList;
	public:
		//inventory
		static const int INV_WIDTH = 800, INV_HEIGHT = 600, INV_TILE_SIZE = 50, INV_BORDER = 1;
		std::vector<int> inventoryOffset, invCraftingOffset, invResultOffset, invInventoryOffset, invActionBarOffset;
		int invTileSize, invBorder;
		float invScale;

		GUI(void);
		~GUI(void);
		GUI(GameData& data);
		void loadResources();
		void drawGUI(sf::RenderWindow& mainWindow, GameData& data);
		void drawGrid(sf::RenderWindow& mainWindow, GameData& data);
		void drawDevInfo(sf::RenderWindow& mainWindow, GameData& data);
		void drawActionBar(sf::RenderWindow& mainWindow, GameData& data);
		void drawPlayerStatus(sf::RenderWindow& mainWindow, GameData& data);
		void drawInteractionMenu(sf::RenderWindow& mainWindow, GameData& data);
		void drawInventory(sf::RenderWindow& mainWindow, GameData& data);
		void drawHeightMap(sf::RenderWindow& mainWindow, GameData& data);
		void drawHeldItem(sf::RenderWindow& mainWindow, GameData& data);
};

#endif