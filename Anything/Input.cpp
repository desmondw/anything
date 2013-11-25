#include "Input.h"

Input::Input(void)
{
}

Input::~Input(void)
{
}

void Input::handleInput(sf::RenderWindow& mainWindow, GameData& data, Audio& audio, Visual& visual)
{
	//TODO create a 2xN array (N = possible actions) with the input set in one column (constant) and a string REACTION_IN_OTHER_COLUMN (configurable by user)
	//then when input is sent, match it against the array and return the string REACTION as the basis for a switch statement
	sf::Event input;
    while (mainWindow.GetEvent(input))
    {
        if (input.Type == sf::Event::Closed) //window closed
            mainWindow.Close();
		else if (input.Type == sf::Event::KeyPressed) //key pressed
			keyPress(mainWindow, data, audio, visual, input);
		else if (input.Type == sf::Event::MouseButtonReleased) //mouse button clicked
			mouseClick(mainWindow, data, audio, visual, input);
		else if (input.Type == sf::Event::MouseWheelMoved)
		{
			if (input.MouseWheel.Delta > 0 && data.guiData.activeItemSlot > 0)
				data.guiData.activeItemSlot--;
			else if (input.MouseWheel.Delta < 0 && data.guiData.activeItemSlot < 2)
				data.guiData.activeItemSlot++;
		}
		else if (input.Type == sf::Event::MouseMoved)
		{
			data.guiData.cursorPosition[0] = input.MouseMove.X;
			data.guiData.cursorPosition[1] = input.MouseMove.Y;
		}
    }
}

void Input::mouseClick(sf::RenderWindow& mainWindow, GameData& data, Audio& audio, Visual& visual, sf::Event& input)
{
	switch (input.MouseButton.Button)
	{
		case sf::Mouse::Left:
			if (data.guiData.inventoryOpen) //TODO: efficiancy vs. readability tradeoff
			{
				int clickedItem = -1;
				bool withinX, withinY;

				//crafting
				withinX = input.MouseButton.X > visual.gui.invCraftingOffset[0] && input.MouseButton.X < visual.gui.invCraftingOffset[0] + data.guiData.craftingGrid.size()*(visual.gui.invTileSize + visual.gui.invBorder);
				withinY = input.MouseButton.Y > visual.gui.invCraftingOffset[1] && input.MouseButton.Y < visual.gui.invCraftingOffset[1] + data.guiData.craftingGrid[0].size()*(visual.gui.invTileSize + visual.gui.invBorder);
				if (withinX && withinY)
				{
					//selects item based on mouse location, grid offset, and tile size / border
					clickedItem = data.guiData.craftingGrid[(input.MouseButton.X - visual.gui.invCraftingOffset[0]) / (visual.gui.invTileSize + visual.gui.invBorder)][(input.MouseButton.Y - visual.gui.invCraftingOffset[1]) / (visual.gui.invTileSize + visual.gui.invBorder)];

					//takes, replaces, or places item at clickedItem
					data.guiData.craftingGrid[(input.MouseButton.X - visual.gui.invCraftingOffset[0]) / (visual.gui.invTileSize + visual.gui.invBorder)][(input.MouseButton.Y - visual.gui.invCraftingOffset[1]) / (visual.gui.invTileSize + visual.gui.invBorder)] = moveItem(data, clickedItem);
				}

				//result
				withinX = input.MouseButton.X > visual.gui.invResultOffset[0] && input.MouseButton.X < visual.gui.invResultOffset[0] + visual.gui.invTileSize + visual.gui.invBorder;
				withinY = input.MouseButton.Y > visual.gui.invResultOffset[1] && input.MouseButton.Y < visual.gui.invResultOffset[1] + visual.gui.invTileSize + visual.gui.invBorder;
				if (withinX && withinY)
				{
					//allows only taking items
					if (!data.guiData.isHoldingItem && data.guiData.craftingResult >= 0) //no item held, item in tile
					{
						data.guiData.isHoldingItem = true;
						data.guiData.heldItem = data.guiData.craftingResult;
						data.guiData.craftingResult = -1;
					}
				}

				//inventory
				withinX = input.MouseButton.X > visual.gui.invInventoryOffset[0] && input.MouseButton.X < visual.gui.invInventoryOffset[0] + (data.world.getPlayer().inventory.size()-1)*(visual.gui.invTileSize + visual.gui.invBorder);
				withinY = input.MouseButton.Y > visual.gui.invInventoryOffset[1] && input.MouseButton.Y < visual.gui.invInventoryOffset[1] + data.world.getPlayer().inventory[0].size()*(visual.gui.invTileSize + visual.gui.invBorder);
				if (withinX && withinY)
				{
					//selects item based on mouse location, grid offset, and tile size / border
					clickedItem = data.world.getPlayer().inventory[(input.MouseButton.X - visual.gui.invInventoryOffset[0]) / (visual.gui.invTileSize + visual.gui.invBorder)][(input.MouseButton.Y - visual.gui.invInventoryOffset[1]) / (visual.gui.invTileSize + visual.gui.invBorder)];

					//takes, replaces, or places item at clickedItem
					data.world.getPlayer().inventory[(input.MouseButton.X - visual.gui.invInventoryOffset[0]) / (visual.gui.invTileSize + visual.gui.invBorder)][(input.MouseButton.Y - visual.gui.invInventoryOffset[1]) / (visual.gui.invTileSize + visual.gui.invBorder)] = moveItem(data, clickedItem);
				}

				//action bar
				withinX = input.MouseButton.X > visual.gui.invActionBarOffset[0] && input.MouseButton.X < visual.gui.invActionBarOffset[0] + data.world.getPlayer().actionBar.size()*(visual.gui.invTileSize + visual.gui.invBorder);
				withinY = input.MouseButton.Y > visual.gui.invActionBarOffset[1] && input.MouseButton.Y < visual.gui.invActionBarOffset[1] + data.world.getPlayer().actionBar[0].size()*(visual.gui.invTileSize + visual.gui.invBorder);
				if (withinX && withinY)
				{
					//selects item based on mouse location, grid offset, and tile size / border
					clickedItem = data.world.getPlayer().actionBar[(input.MouseButton.X - visual.gui.invActionBarOffset[0]) / (visual.gui.invTileSize + visual.gui.invBorder)][(input.MouseButton.Y - visual.gui.invActionBarOffset[1]) / (visual.gui.invTileSize + visual.gui.invBorder)];

					//takes, replaces, or places item at clickedItem
					data.world.getPlayer().actionBar[(input.MouseButton.X - visual.gui.invActionBarOffset[0]) / (visual.gui.invTileSize + visual.gui.invBorder)][(input.MouseButton.Y - visual.gui.invActionBarOffset[1]) / (visual.gui.invTileSize + visual.gui.invBorder)] = moveItem(data, clickedItem);
				}
			}
			else if (data.guiData.interactMenuOpen)
			{

			}
			else if (data.guiData.fullMenuOpen)
			{

			}
			else //in game
			{
				switch (data.world.getPlayer().actionBar[0][data.guiData.activeItemSlot]) //item
				{
					case -1:
						if (data.world.isPlayerFacingTile())
						{
							Tile facedTile = data.world.getPlayerFacedTile();
							if (facedTile.hasUnit)
								; //punch
							else if (facedTile.hasImprovement)
							{
								switch (facedTile.getImprovement().ID) //improvements
								{
									case 1:
										//eat
										data.world.getPlayer().hunger = data.world.getPlayer().maxHunger;
										endTurn(data);
										break;
								}
							}
							else
							{
								switch (facedTile.getTerrain().ID) //terrain
								{
									case 3:
										//drink
										data.world.getPlayer().thirst = data.world.getPlayer().maxThirst;
										endTurn(data);
										break;
								}
							}
						}
						break;
					//other items
				}
			}
			break;
	}
}

void Input::keyPress(sf::RenderWindow& mainWindow, GameData& data, Audio& audio, Visual& visual, sf::Event& input)
{
	//global
	switch (input.Key.Code)
	{
		case sf::Key::Tilde:
			if (data.settings.devInfoOn)
				data.settings.devInfoOn = false;
			else
				data.settings.devInfoOn = true;
			break;
		case sf::Key::F9:
			if (data.settings.vsyncOn)
			{
				data.settings.vsyncOn = false;
				mainWindow.UseVerticalSync(data.settings.vsyncOn);
			}
			else
			{
				data.settings.vsyncOn = true;
				mainWindow.UseVerticalSync(data.settings.vsyncOn);
			}
			break;
		case sf::Key::F11:
			if (data.settings.fullscreenOn)
			{
				data.settings.fullscreenOn = false;
				mainWindow.Create(sf::VideoMode(data.settings.WIN_WIDTH, data.settings.WIN_HEIGHT, 32), "Anything", sf::Style::Close);
			}
			else
			{
				data.settings.fullscreenOn = true;
				mainWindow.Create(sf::VideoMode(data.settings.WIN_WIDTH, data.settings.WIN_HEIGHT, 32), "Anything", sf::Style::Fullscreen);
			}
			break;
	}
	
	if (data.guiData.fullMenuOpen) //full menu
	{
		switch (input.Key.Code)
		{
			case sf::Key::Escape:
				mainWindow.Close();
				break;
		}
	}
	else //game
	{
		if (data.guiData.interactMenuOpen || data.guiData.inventoryOpen) //in interaction menu / inventory
		{
			switch (input.Key.Code)
			{
				case sf::Key::Escape:
					data.guiData.fullMenuOpen = false;
					if (!data.guiData.isHoldingItem) //no item held
						data.guiData.inventoryOpen = false;
					data.guiData.interactMenuOpen = false;
					break;
				case sf::Key::E:
					data.guiData.interactMenuOpen = false;
					break;
				case sf::Key::C:
					if (!data.guiData.isHoldingItem) //no item held
						data.guiData.inventoryOpen = false;
					break;
				case sf::Key::Up:
					moveMenuSelection(data, 2);
					break;
				case sf::Key::W:
					moveMenuSelection(data, 2);
					break;
				case sf::Key::Down:
					moveMenuSelection(data, 0);
					break;
				case sf::Key::S:
					moveMenuSelection(data, 0);
					break;
				case sf::Key::Left:
					moveMenuSelection(data, 1);
					break;
				case sf::Key::A:
					moveMenuSelection(data, 1);
					break;
				case sf::Key::Right:
					moveMenuSelection(data, 3);
					break;
				case sf::Key::D:
					moveMenuSelection(data, 3);
					break;
			}
		}
		else //not in menu
		{
			switch (input.Key.Code)
			{
				case sf::Key::Escape:
					mainWindow.Close();
					//data.guiData.fullMenuOpen = true;
					break;
				case sf::Key::Q:
					if (data.settings.gridOn)
						data.settings.gridOn = false;
					else
						data.settings.gridOn = true;
					break;
				case sf::Key::E:
					//data.guiData.interactMenuOpen = true; //TODO: remove all interaction menu code
					break;
				case sf::Key::C:
					data.guiData.inventoryOpen = true;
					break;
				case sf::Key::M:
					if (data.guiData.heightMapOpen)
						data.guiData.heightMapOpen = false;
					else
						data.guiData.heightMapOpen = true;
					break;
				case sf::Key::N:
					data.newGame();
					break;
				case sf::Key::Up:
					movePlayer(data, 2);
					break;
				case sf::Key::W:
					movePlayer(data, 2);
					break;
				case sf::Key::Down:
					movePlayer(data, 0);
					break;
				case sf::Key::S:
					movePlayer(data, 0);
					break;
				case sf::Key::Left:
					movePlayer(data, 1);
					break;
				case sf::Key::A:
					movePlayer(data, 1);
					break;
				case sf::Key::Right:
					movePlayer(data, 3);
					break;
				case sf::Key::D:
					movePlayer(data, 3);
					break;
			}
		}
	}
}

void Input::moveMenuSelection(GameData& data, int direction)
{
	if (data.guiData.interactMenuOpen)
	{
		//TODO
	}
	else
	{
		//TODO
	}
}

void Input::movePlayer(GameData& data, int direction)
{
	if (testValidMove(data, direction))
	{
		int oldX = data.world.playerPos[0];
		int newX = data.world.playerPos[0];
		int oldY = data.world.playerPos[1];
		int newY = data.world.playerPos[1];
	
		switch (direction)
		{
			case 0: //south
				newY++;
				data.world.playerPos[1]++;
				break;
			case 1: //west
				newX--;
				data.world.playerPos[0]--;
				break;
			case 2: //north
				newY--;
				data.world.playerPos[1]--;
				break;
			case 3: //east
				newX++;
				data.world.playerPos[0]++;
				break;
		}

		data.world.moveUnit(oldX, oldY, newX, newY);
		endTurn(data);
	}

	data.world.getPlayer().changeDirection(direction);
}

bool Input::testValidMove(GameData& data, int direction)
{
	data.world.getPlayer().direction = direction;
	int oldX = data.world.playerPos[0];
	int oldY = data.world.playerPos[1];
	int newX = data.world.playerPos[0];
	int newY = data.world.playerPos[1];

	switch (direction)
	{
		case 0: //south
			newY++;
			break;
		case 1: //west
			newX--;
			break;
		case 2: //north
			newY--;
			break;
		case 3: //east
			newX++;
			break;
	}

	if (newX >= 0 && newX < data.world.WORLD_SIZE && newY >= 0 && newY < data.world.WORLD_SIZE) //within world
		if (!data.getBoard()[newX][newY].hasUnit) //has no unit
			if (data.getBoard()[newX][newY].getTerrain().passable || (data.getBoard()[newX][newY].getTerrain().ID == 3 && data.getBoard()[oldX][oldY].getUnit().canSwim)) //passable, or is water and unit can swim
				if (!data.getBoard()[newX][newY].hasImprovement)
					return true;
				else if (data.getBoard()[newX][newY].getImprovement().passable)
					return true;
	return false;
}

void Input::endTurn(GameData& data)
{
	data.world.time++;

	//update hunger and thirst
	if (data.world.time % 10 == 0 && data.world.getPlayer().thirst > 0)
		data.world.getPlayer().thirst--;
	if (data.world.time % 20 == 0 && data.world.getPlayer().hunger > 0)
		data.world.getPlayer().hunger--;
	
	//take away health for starving/dehydrated
	if (data.world.getPlayer().hunger <= 0)
		data.world.getPlayer().health--;
	if (data.world.getPlayer().thirst <= 0)
		data.world.getPlayer().health--;

	//AI Moves
	//Physics
	
	//test game loss
	if (data.world.getPlayer().health <= 0)
		data.world.newGame();
}

int Input::moveItem(GameData& data, int clickedItem)
{
	if (data.guiData.isHoldingItem && clickedItem >=0) //item held, item in tile
	{

	}
	else if (data.guiData.isHoldingItem) //item held, no item in tile
	{
		clickedItem = data.guiData.heldItem;
		data.guiData.heldItem = -1;
		data.guiData.isHoldingItem = false;
	}
	else if (clickedItem >= 0) //no item held, item in tile
	{
		data.guiData.isHoldingItem = true;
		data.guiData.heldItem = clickedItem;
		clickedItem = -1;
	}

	return clickedItem;
}