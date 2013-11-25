#include <SFML/Graphics.hpp>

#include "GameData.h"
#include "Input.h"
#include "Audio.h"
#include "Visual.h"

sf::RenderWindow mainWindow; //game window
GameData data; //data
Input input; //input
Audio audio; //audio output
Visual visual(data); //visual output

void intializeVideoSettings()
{
	mainWindow.UseVerticalSync(data.settings.vsyncOn);
	if (data.settings.fullscreenOn)
		mainWindow.Create(sf::VideoMode(data.settings.WIN_WIDTH, data.settings.WIN_HEIGHT, 32), "Anything", sf::Style::Fullscreen);
	else
		mainWindow.Create(sf::VideoMode(data.settings.WIN_WIDTH, data.settings.WIN_HEIGHT, 32), "Anything", sf::Style::Close);
}

void main()
{
	srand (time(NULL)); //seed random gen
	data.newGame(); //generate new world
	intializeVideoSettings(); //implement initial window settings

	//main loop
    while (mainWindow.IsOpened())
    {
		input.handleInput(mainWindow, data, audio, visual);
		audio.playMusic();
		visual.drawGraphics(mainWindow, data);
    }
}