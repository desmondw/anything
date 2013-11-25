#ifndef _GAMEDATA_H
#define _GAMEDATA_H

#include "World.h"
#include "Settings.h"
#include "GUIData.h"

class GameData
{
	public:
		World world;
		Settings settings;
		GUIData guiData;

		GameData(void);
		~GameData(void);
		void newGame();
		std::vector<std::vector<Tile>>& getBoard();
};

#endif