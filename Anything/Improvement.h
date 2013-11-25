#ifndef _IMPROVEMENT_H
#define _IMPROVEMENT_H

#include <string>
#include <SFML/Graphics.hpp>

class Improvement
{
	private:

	public:
		int ID;
		std::string name, imageName;
		bool passable, gatherable, destroyable;
		std::vector<std::string> gatherList;
		int durability;

		Improvement(void);
		~Improvement(void);
		Improvement(int ID, std::string name, std::string imageName, bool passable, bool gatherable, bool destroyable);
};

#endif