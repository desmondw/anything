#include "Tile.h"

Tile::Tile(void)
{
}

Tile::~Tile(void)
{
}

Tile::Tile(int column, int row, Terrain terrain)
{
	this->column = column;
	this->row = row;
	this->terrain = terrain;
	hasImprovement = false;
	hasUnit = false;
}

Tile::Tile(int column, int row, Terrain terrain, Improvement improvement)
{
	this->column = column;
	this->row = row;
	this->terrain = terrain;
	this->improvement = improvement;
	hasImprovement = true;
	hasUnit = false;
}

Tile::Tile(int column, int row, Terrain terrain, Unit unit)
{
	this->column = column;
	this->row = row;
	this->terrain = terrain;
	this->unit = unit;
	hasImprovement = false;
	hasUnit = true;
}

Tile::Tile(int column, int row, Terrain terrain, Improvement improvement, Unit unit)
{
	this->column = column;
	this->row = row;
	this->terrain = terrain;
	this->improvement = improvement;
	this->unit = unit;
	hasImprovement = true;
	hasUnit = true;
}

int Tile::getColumn()
{
	return column;
}

int Tile::getRow()
{
	return row;
}

Terrain Tile::getTerrain()
{
	return terrain;
}

Improvement Tile::getImprovement()
{
	return improvement;
}

Unit& Tile::getUnit()
{
	return unit;
}

void Tile::addImprovement(Improvement improvement)
{
	hasImprovement = true;
	this->improvement = improvement;
}

void Tile::removeImprovement()
{
	hasImprovement = false;
	this->improvement = Improvement();
}

void Tile::addUnit(Unit unit)
{
	hasUnit = true;
	this->unit = unit;
}

void Tile::removeUnit()
{
	hasUnit = false;
	this->unit = Unit();
}

bool Tile::compare(Tile otherTile)
{
	if (otherTile.getColumn() == column && otherTile.getRow() == row)
		return true;
	return false;
}