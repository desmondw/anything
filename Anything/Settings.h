#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <SFML/Graphics.hpp>
#include <vector>

class Settings
{
	private:

	public:
		static const int WIN_WIDTH = 1024, WIN_HEIGHT = 768;
		static const int TILE_SIZE = 64; //TODO move to World, as this isn't a NORMAL USER setting
		bool fullscreenOn, vsyncOn, gridOn, devInfoOn;

		Settings(void);
		~Settings(void);
};

#endif