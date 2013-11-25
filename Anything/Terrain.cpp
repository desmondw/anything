#include "Terrain.h"

Terrain::Terrain(void)
{
}

Terrain::~Terrain(void)
{
}

Terrain::Terrain(int ID, std::string name, std::string imageName, bool passable, bool gatherable, bool improvable)
{
	this->ID = ID;
	this->name = name;
	this->imageName = imageName;
	this->passable = passable;
	this->gatherable = gatherable;
	this->improvable = improvable;
}