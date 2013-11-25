#include "GameData.h"

GameData::GameData(void)
{
	settings = Settings();
	guiData = GUIData();
	world = World();
}

GameData::~GameData(void)
{
}

std::vector<std::vector<Tile>>& GameData::getBoard()
{
	return world.getBoard();
}

void GameData::newGame()
{
	world.newGame();
}