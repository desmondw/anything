#ifndef _WORLD_H
#define _WORLD_H

#include <math.h>
#include <vector>
#include "Tile.h"
#include "Settings.h"

class World //TODO: remove inheritence, should work fine
{
	private:
		std::vector<std::vector<Tile>> board;
		std::vector<std::vector<int>> heightMap;

		//ID lists for drawables
		std::vector<Terrain> terrainList;
		std::vector<Improvement> improvementList;
		std::vector<Unit> unitList;
	public:
		int time;
		static const int MAX_TIME = 1000000000;
		std::vector<int> playerPos;
		static const int WORLD_SIZE = 257;
		static const int TERRAIN_LIST_SIZE = 5, IMPROVEMENT_LIST_SIZE = 6, UNIT_LIST_SIZE = 3, ITEM_LIST_SIZE = 3;
		sf::Image heightMapImage;

		World(void);
		~World(void);
		std::vector<std::vector<Tile>>& getBoard();
		void newGame();
		void initializeTiles();
		void fillUnitImageList(std::vector<std::string>& unitImageList, std::string name);
		void moveUnit(int oldX, int oldY, int newX, int newY);
		void addUnit(int ID, int x, int y);
		Unit& getPlayer();
		bool isPlayerFacingTile();
		Tile getPlayerFacedTile();
		void createHeightMapImage();
		void calculateHeightMap(int variance);
		void calculateHeightMap(int variance, std::vector<int> seed);
		void calculateHeightMap(std::vector<int> topLeft, std::vector<int> topRight, std::vector<int> bottomLeft, std::vector<int> bottomRight, int variance);
};

#endif