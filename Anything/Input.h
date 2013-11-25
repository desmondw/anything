#ifndef _INPUT_H
#define _INPUT_H

#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "Audio.h"
#include "Visual.h"

class Input
{
	private:

	public:
		Input(void);
		~Input(void);
		void handleInput(sf::RenderWindow& mainWindow, GameData& data, Audio& audio, Visual& visual);
		void mouseClick(sf::RenderWindow& mainWindow, GameData& data, Audio& audio, Visual& visual, sf::Event& input);
		void keyPress(sf::RenderWindow& mainWindow, GameData& data, Audio& audio, Visual& visual, sf::Event& input);
		
		void moveMenuSelection(GameData& data, int direction);
		void movePlayer(GameData& data, int direction);
		bool testValidMove(GameData& data, int direction);
		void endTurn(GameData& data);
		int moveItem(GameData& data, int clickedItem);
};

#endif