#ifndef _VISUAL_H
#define _VISUAL_H

#include <SFML/Graphics.hpp>
#include "WorldGraphics.h"
#include "GUI.h"
#include "FullMenu.h"
#include "GameData.h"

class Visual
{
	private:

	public:
		FullMenu fullMenu;
		GUI gui;
		WorldGraphics worldGraphics;

		Visual(void);
		~Visual(void);
		Visual(GameData& data);
		void drawGraphics(sf::RenderWindow& mainWindow, GameData& data);
};

#endif