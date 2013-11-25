#ifndef _TILE_H
#define _TILE_H

#include "Terrain.h"
#include "Improvement.h"
#include "Unit.h"

class Tile
{
	private:
		int column, row;
		Terrain terrain;
		Improvement improvement;
		Unit unit;
	public:
		bool hasImprovement, hasUnit;

		Tile(void);
		~Tile(void);
		Tile(int column, int row, Terrain terrain);
		Tile(int column, int row, Terrain terrain, Improvement improvement);
		Tile(int column, int row, Terrain terrain, Unit unit);
		Tile(int column, int row, Terrain terrain, Improvement improvement, Unit unit);
		int getRow();
		int getColumn();
		Terrain getTerrain();
		Improvement getImprovement();
		Unit& getUnit();
		void addImprovement(Improvement improvement);
		void removeImprovement();
		void addUnit(Unit unit);
		void removeUnit();
		bool compare(Tile otherTile);
};

#endif