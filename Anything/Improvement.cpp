#include "Improvement.h"

Improvement::Improvement(void)
{
}

Improvement::~Improvement(void)
{
}

Improvement::Improvement(int ID, std::string name, std::string imageName, bool passable, bool gatherable, bool destroyable)
{
	this->ID = ID;
	this->name = name;
	this->imageName = imageName;
	this->passable = passable;
	this->gatherable = gatherable;
	this->destroyable = destroyable;
}