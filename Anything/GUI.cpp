#include "GUI.h"

GUI::GUI(void)
{
}

GUI::~GUI(void)
{
}

GUI::GUI(GameData& data)
{	
	itemImgList.resize(data.world.ITEM_LIST_SIZE);
	loadResources();

	//image positioning and scale
	invScale = static_cast<float>(data.settings.WIN_HEIGHT) * .8 / INV_HEIGHT; //.8 = 80% of screen height
	
	inventoryOffset.resize(2);
	invCraftingOffset.resize(2);
	invResultOffset.resize(2);
	invInventoryOffset.resize(2);
	invActionBarOffset.resize(2);

	invTileSize = INV_TILE_SIZE * invScale;
	invBorder = INV_BORDER * invScale;

	inventoryOffset[0] = (data.settings.WIN_WIDTH - INV_WIDTH * invScale) /2;
	inventoryOffset[1] = (data.settings.WIN_HEIGHT - INV_HEIGHT * invScale) /2;
	invCraftingOffset[0] = inventoryOffset[0] + 251 * invScale;
	invCraftingOffset[1] = inventoryOffset[1] + 151 * invScale;
	invResultOffset[0] = inventoryOffset[0] + 501 * invScale;
	invResultOffset[1] = inventoryOffset[1] + 201 * invScale;
	invInventoryOffset[0] = inventoryOffset[0] + 201 * invScale;
	invInventoryOffset[1] = inventoryOffset[1] + 351 * invScale;
	invActionBarOffset[0] = inventoryOffset[0] + 551 * invScale;
	invActionBarOffset[1] = inventoryOffset[1] + 351 * invScale;
}

void GUI::loadResources()
{
	font.LoadFromFile("bin/arial.ttf", 30);

	
	//gui window skins
	inventoryImage.SetSmooth(false);
	inventoryImage.LoadFromFile("bin/graphics/gui/inventory.png");

	
	//items
	sf::Image image;
	image.SetSmooth(false);
	std::string folder;

	folder = "bin/graphics/item/";
	image.LoadFromFile(folder + "pickaxe.png");
	itemImgList[0] = image;
	image.LoadFromFile(folder + "shovel.png");
	itemImgList[1] = image;
	image.LoadFromFile(folder + "axe.png");
	itemImgList[2] = image;
}

void GUI::drawGUI(sf::RenderWindow& mainWindow, GameData& data)
{
	//world layer
	if (data.settings.gridOn)
		drawGrid(mainWindow, data);

	//always shown layer
	drawPlayerStatus(mainWindow, data);
	drawActionBar(mainWindow, data);

	//conditional layers
	if (data.guiData.interactMenuOpen)
		drawInteractionMenu(mainWindow, data);
	if (data.guiData.inventoryOpen)
		drawInventory(mainWindow, data);
	if (data.guiData.heightMapOpen)
		drawHeightMap(mainWindow, data);
	if (data.settings.devInfoOn)
		drawDevInfo(mainWindow, data);
	if (data.guiData.isHoldingItem)
		drawHeldItem(mainWindow, data);
}

void GUI::drawGrid(sf::RenderWindow& mainWindow, GameData& data)
{
	const int GRID_WIDTH = 1;
	int xPos, yPos;
	int xOffset = (data.settings.WIN_WIDTH / 2) - (data.settings.TILE_SIZE * data.world.playerPos[0]) - data.settings.TILE_SIZE / 2;
	int yOffset = (data.settings.WIN_HEIGHT / 2) - (data.settings.TILE_SIZE * data.world.playerPos[1]) - data.settings.TILE_SIZE / 2;

	for (int i=0; i<data.world.WORLD_SIZE+1; i++)
	{
		xPos = i * data.settings.TILE_SIZE + xOffset;
		mainWindow.Draw(sf::Shape::Line(xPos, yOffset, xPos, data.settings.TILE_SIZE*data.world.WORLD_SIZE + yOffset, GRID_WIDTH, sf::Color::Black));
	}

	for (int j=0; j<data.world.WORLD_SIZE+1; j++)
	{
		yPos = j * data.settings.TILE_SIZE + yOffset;
		mainWindow.Draw(sf::Shape::Line(xOffset, yPos, data.settings.TILE_SIZE*data.world.WORLD_SIZE + xOffset, yPos, GRID_WIDTH, sf::Color::Black));
	}
}

void GUI::drawDevInfo(sf::RenderWindow& mainWindow, GameData& data)
{
	const int OUTLINE = 3;
	int offsetX = OUTLINE;
	int offsetY = OUTLINE;

	//draw window
	mainWindow.Draw(sf::Shape::Rectangle(offsetX, offsetY, data.settings.WIN_WIDTH/5, data.settings.WIN_HEIGHT/5, sf::Color(220, 220, 220, 200), OUTLINE, sf::Color::Black));

	//draw text
	sf::String text("", font, 15);
	text.SetPosition(offsetX, offsetY);
	std::ostringstream sstream;

	sstream << "FPS: ";
	sstream << static_cast<int>(1 / mainWindow.GetFrameTime());
	sstream << "\nTime: ";
	sstream << data.world.time;
	sstream << "\nPlayer Position: ";
	sstream << data.world.playerPos[0];
	sstream << ", ";
	sstream << data.world.playerPos[1];
	sstream << "\nCursor Position: ";
	sstream << data.guiData.cursorPosition[0];
	sstream << ", ";
	sstream << data.guiData.cursorPosition[1];
	
	sstream << "\nItem held: ";
	if (data.guiData.isHoldingItem)
		sstream << "yes";
	else
		sstream << "no";
	sstream << "\nHeld item: ";
	sstream << data.guiData.heldItem;
	sstream << "\nActive item slot: ";
	sstream << data.guiData.activeItemSlot;
	sstream << "\nActive item: ";
	sstream << data.world.getPlayer().actionBar[0][data.guiData.activeItemSlot];

	text.SetText(sstream.str());
	sstream.end;
	
	text.SetColor(sf::Color::Black);
	mainWindow.Draw(text);
}

void GUI::drawPlayerStatus(sf::RenderWindow& mainWindow, GameData& data)
{
	const int ICON_SIZE = 50;
	int groupOffsetX = 0;
	int groupOffsetY = data.settings.WIN_HEIGHT - ICON_SIZE * 3;
	sf::Image image;
	image.SetSmooth(false);
	sf::Sprite sprite;
	sprite.Scale((ICON_SIZE / 100.f), (ICON_SIZE / 100.f));

	//health icon
	sprite.SetX(groupOffsetX);
	sprite.SetY(groupOffsetY);
	image.LoadFromFile("bin/graphics/gui/healthIcon.png");
	sprite.SetImage(image);
	mainWindow.Draw(sprite);

	//water icon
	sprite.SetX(groupOffsetX);
	sprite.SetY(groupOffsetY + ICON_SIZE);
	image.LoadFromFile("bin/graphics/gui/waterIcon.png");
	sprite.SetImage(image);
	mainWindow.Draw(sprite);

	//food icon
	sprite.SetX(groupOffsetX);
	sprite.SetY(groupOffsetY + ICON_SIZE*2);
	image.LoadFromFile("bin/graphics/gui/foodIcon.png");
	sprite.SetImage(image);
	mainWindow.Draw(sprite);

	const int BAR_WIDTH = data.settings.WIN_WIDTH / 5;
	const int BAR_HEIGHT = data.settings.WIN_HEIGHT / 50;
	int x, y;
	const int BAR_XBUFFER = 10;
	const int BAR_YBUFFER = ICON_SIZE/2 - BAR_HEIGHT/2;

	//health bar
	x = groupOffsetX + ICON_SIZE + BAR_XBUFFER;
	y = groupOffsetY + BAR_YBUFFER;
	mainWindow.Draw(sf::Shape::Rectangle(x, y, x + BAR_WIDTH, y + BAR_HEIGHT, sf::Color::White, 2.0, sf::Color::Black));
	mainWindow.Draw(sf::Shape::Rectangle(x, y, (x + BAR_WIDTH*(static_cast<float>(data.world.getPlayer().health) / data.world.getPlayer().maxHealth)), y + BAR_HEIGHT, sf::Color::Red, 2.0, sf::Color::Black));

	//thirst bar
	x = groupOffsetX + ICON_SIZE + BAR_XBUFFER;
	y = groupOffsetY + ICON_SIZE + BAR_YBUFFER;
	mainWindow.Draw(sf::Shape::Rectangle(x, y, x + BAR_WIDTH, y + BAR_HEIGHT, sf::Color::White, 2.0, sf::Color::Black));
	mainWindow.Draw(sf::Shape::Rectangle(x, y, (x + BAR_WIDTH*(static_cast<float>(data.world.getPlayer().thirst) / data.world.getPlayer().maxThirst)), y + BAR_HEIGHT, sf::Color::Blue, 2.0, sf::Color::Black));

	//hunger bar
	x = groupOffsetX + ICON_SIZE + BAR_XBUFFER;
	y = groupOffsetY + ICON_SIZE * 2 + BAR_YBUFFER;
	mainWindow.Draw(sf::Shape::Rectangle(x, y, x + BAR_WIDTH, y + BAR_HEIGHT, sf::Color::White, 2.0, sf::Color::Black));
	mainWindow.Draw(sf::Shape::Rectangle(x, y, (x + BAR_WIDTH*(static_cast<float>(data.world.getPlayer().hunger) / data.world.getPlayer().maxHunger)), y + BAR_HEIGHT, sf::Color::Green, 2.0, sf::Color::Black));
}

void GUI::drawActionBar(sf::RenderWindow& mainWindow, GameData& data)
{
	//TODO set scaling to window size (add universal scale for window size?)
	int groupOffsetX = data.settings.WIN_WIDTH - 100;
	int groupOffsetY = data.settings.WIN_HEIGHT - 200;

	sf::Sprite sprite;
	sf::Image circleImage;
	circleImage.SetSmooth(false);
	sf::Sprite circleSprite;

	circleImage.LoadFromFile("bin/graphics/gui/circle.png");
	circleSprite.SetImage(circleImage);
	
	sf::Sprite scaledCircleSprite(circleSprite);
	sf::Sprite scaledSprite(sprite);
	int offsetX, offsetY = 0;
	int increment;
	for (int i=0; i<data.world.getPlayer().actionBar[0].size(); i++)
	{
		if (i == data.guiData.activeItemSlot) //selected item
		{
			circleSprite.SetScale(1, 1);
			sprite.SetScale(1, 1);
			offsetX = 0;
			increment = 100;
		}
		else
		{
			circleSprite.SetScale(.5, .5);
			sprite.SetScale(.5, .5);
			offsetX = 50;
			increment = 50;
		}

		circleSprite.SetX(groupOffsetX + offsetX);
		circleSprite.SetY(groupOffsetY + offsetY);
		sprite.SetX(groupOffsetX + offsetX);
		sprite.SetY(groupOffsetY + offsetY);
		
		mainWindow.Draw(circleSprite);

		if (data.world.getPlayer().actionBar[0][i] >= 0)
		{
			sprite.SetImage(itemImgList[data.world.getPlayer().actionBar[0][i]]);
			mainWindow.Draw(sprite);
		}

		offsetY += increment;
	}
}

void GUI::drawInteractionMenu(sf::RenderWindow& mainWindow, GameData& data)
{
	const int WIDTH = 300, HEIGHT = 500, OUTLINE = 3;
	const float SCALE = static_cast<float>(HEIGHT) / MIN_RESOLUTION_Y; //scales image based on lowest supported resolution

	int groupOffsetX = data.settings.WIN_WIDTH - WIDTH - OUTLINE;
	int groupOffsetY = OUTLINE;

	int offsetX = groupOffsetX;
	int offsetY = groupOffsetY;
	Tile selectedTile;

	switch (data.world.getPlayer().direction) //select tile based on direction
	{
		case 0: //south
			if (data.world.playerPos[1] + 1 < data.world.WORLD_SIZE)
				selectedTile = data.world.getBoard()[data.world.playerPos[0]][data.world.playerPos[1]+1];
			break;
		case 1: //west
			if (data.world.playerPos[0] - 1 > 0)
				selectedTile = data.world.getBoard()[data.world.playerPos[0]-1][data.world.playerPos[1]];
			break;
		case 2: //north
			if (data.world.playerPos[1] - 1 > 0)
				selectedTile = data.world.getBoard()[data.world.playerPos[0]][data.world.playerPos[1]-1];
			break;
		case 3: //east
			if (data.world.playerPos[0] - 1 < data.world.WORLD_SIZE)
				selectedTile = data.world.getBoard()[data.world.playerPos[0]-1][data.world.playerPos[1]];
			break;
	}

	//draw window
	mainWindow.Draw(sf::Shape::Rectangle(offsetX, offsetY, offsetX + WIDTH, offsetY + HEIGHT, sf::Color(220, 220, 220, 200), OUTLINE, sf::Color::Black));

	//draw text
	sf::String text("", font, 15);
	text.SetPosition(offsetX, offsetY);
	std::ostringstream sstream;

	//if unit in selectedTile
		//list standard option against a unit
		//add cancel option

	//else if improvement in tile
		//list interaction options for the improvement
		//add option to destroy improvement, if destroyable
		//add cancel option

	//else
		//list terrain improvement options
		//add cancel option




	sstream << "List of options goes here";

	text.SetText(sstream.str());
	sstream.end;
	
	text.SetColor(sf::Color::Black);
	mainWindow.Draw(text);
}

void GUI::drawInventory(sf::RenderWindow& mainWindow, GameData& data)
{
	sf::Sprite sprite;
	sprite.SetScale(invScale, invScale);
	sprite.SetPosition(inventoryOffset[0], inventoryOffset[1]);
	sprite.SetImage(inventoryImage);
	mainWindow.Draw(sprite);
	
	sprite.SetScale(invScale*.5, invScale*.5);
	
	//crafting
	for (int i=0; i<data.guiData.craftingGrid.size(); i++)
	{
		for (int j=0; j<data.guiData.craftingGrid[i].size(); j++)
		{
			if (data.guiData.craftingGrid[i][j] >= 0)
			{
				sprite.SetPosition(invCraftingOffset[0] + i*invTileSize + i*invBorder, invCraftingOffset[1] + j*invTileSize + j*invBorder);
				sprite.SetImage(itemImgList[data.guiData.craftingGrid[i][j]]);
				mainWindow.Draw(sprite);
			}
		}
	}

	//result
	if (data.guiData.craftingResult >= 0)
	{
		sprite.SetPosition(invResultOffset[0], invResultOffset[1]);
		sprite.SetImage(itemImgList[data.guiData.craftingResult]);
		mainWindow.Draw(sprite);
	}

	//inventory
	for (int i=0; i<data.world.getPlayer().inventory.size(); i++)
	{
		for (int j=0; j<data.world.getPlayer().inventory[i].size(); j++)
		{
			if (data.world.getPlayer().inventory[i][j] >= 0)
			{
				sprite.SetPosition(invInventoryOffset[0] + i*invTileSize + i*invBorder, invInventoryOffset[1] + j*invTileSize + j*invBorder);
				sprite.SetImage(itemImgList[data.world.getPlayer().inventory[i][j]]);
				mainWindow.Draw(sprite);
			}
		}
	}
	
	//action bar items
	for (int i=0; i<data.world.getPlayer().actionBar.size(); i++)
	{
		for (int j=0; j<data.world.getPlayer().actionBar[i].size(); j++)
		{
			if (data.world.getPlayer().actionBar[i][j] >= 0)
			{
				sprite.SetPosition(invActionBarOffset[0], invActionBarOffset[1] + j*invTileSize + j*invBorder);
				sprite.SetImage(itemImgList[data.world.getPlayer().actionBar[i][j]]);
				mainWindow.Draw(sprite);
			}
		}
	}
}

void GUI::drawHeightMap(sf::RenderWindow& mainWindow, GameData& data)
{
	sf::Sprite sprite;
	sprite.SetPosition(250, 100);
	sprite.SetImage(data.world.heightMapImage);
	sprite.SetScale(2, 2);

	mainWindow.Draw(sprite);
}

void GUI::drawHeldItem(sf::RenderWindow& mainWindow, GameData& data)
{
	sf::Sprite sprite;
	sprite.SetScale(invScale*.5, invScale*.5);
	sprite.SetPosition(data.guiData.cursorPosition[0], data.guiData.cursorPosition[1]);
	sprite.SetImage(itemImgList[data.guiData.heldItem]);

	mainWindow.Draw(sprite);
}