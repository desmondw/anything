#ifndef _WORLDGRAPHICS_H
#define _WORLDGRAPHICS_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include "Tile.h"
#include "GameData.h"

class WorldGraphics
{
	private:
		//resources
		std::vector<sf::Image> terrainImgList;
		std::vector<sf::Image> improvementImgList;
		std::vector<std::vector<sf::Image>> unitImgList;
		
		sf::Sprite scaleImage(sf::Sprite sprite, GameData& data);
	public:
		WorldGraphics(void);
		~WorldGraphics(void);
		WorldGraphics(GameData& data);
		void loadResources();
		void drawWorld(sf::RenderWindow& mainWindow, GameData& data);
};

#endif