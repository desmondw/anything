#ifndef _GUIDATA_H
#define _GUIDATA_H

#include <vector>

class GUIData
{
	public:
		int activeItemSlot; //range of 0-2
		bool interactMenuOpen;
		bool inventoryOpen;
		bool fullMenuOpen;
		bool heightMapOpen;
		bool isHoldingItem;
		int heldItem;
		std::vector<std::vector<int>> craftingGrid;
		int craftingResult;
		std::vector<std::vector<std::vector<int>>> patternList;
		std::vector<int> resultList;
		std::vector<int> cursorPosition;

		GUIData(void);
		~GUIData(void);
		void initializeCraftingGrid();
		void initializePatternList();
};

#endif