#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <string>
#include <SFML/Graphics.hpp>

class Terrain
{
	private:

	public:
		int ID;
		std::string name, imageName;
		bool passable, gatherable, improvable;
		std::vector<std::string> gatherList, improveList;

		Terrain(void);
		~Terrain(void);
		Terrain(int ID, std::string name, std::string imageName, bool passable, bool gatherable, bool improvable);
};

#endif