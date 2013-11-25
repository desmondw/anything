#include "GUIData.h"

GUIData::GUIData(void)
{
	activeItemSlot = 2;
	interactMenuOpen = false;
	inventoryOpen = false;
	fullMenuOpen = false;
	heightMapOpen = false;
	isHoldingItem = false;
	heldItem = -1;
	craftingGrid = std::vector<std::vector<int>>(3, std::vector<int>(3)); //3x3
	cursorPosition.resize(2);
	cursorPosition[0] = 0;
	cursorPosition[1] = 0;

	initializeCraftingGrid();
	initializePatternList();
}

GUIData::~GUIData(void)
{
}

void GUIData::initializeCraftingGrid()
{
	for (int i=0; i<craftingGrid.size(); i++)
	{
		for (int j=0; j<craftingGrid[i].size(); j++)
		{
			craftingGrid[i][j] = -1;
		}
	}
	craftingGrid[1][1] = 1; //TODO REMOVE TEST CASE

	craftingResult = 1; //TODO REMOVE TEST CASE
}

void GUIData::initializePatternList()
{
	patternList.resize(1);
	resultList.resize(1);

	std::vector<std::vector<int>> pattern(3, std::vector<int>(3)); //3x3
	std::vector<std::vector<int>> emptyPattern(3, std::vector<int>(3, -1)); //3x3 filled with -1
	pattern = emptyPattern;

	//list of patterns
	//TODO: add patterns
}