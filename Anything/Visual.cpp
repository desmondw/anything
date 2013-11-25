#include "Visual.h"

Visual::Visual(void)
{
}

Visual::~Visual(void)
{
}

Visual::Visual(GameData& data)
{
	worldGraphics = WorldGraphics(data);
	gui = GUI(data);
	fullMenu = FullMenu(data);
}

void Visual::drawGraphics(sf::RenderWindow& mainWindow, GameData& data)
{
	mainWindow.Clear(); //clear screen
	
	worldGraphics.drawWorld(mainWindow, data); //draw world
	gui.drawGUI(mainWindow, data); //draw gui

    mainWindow.Display(); //draw screen
}