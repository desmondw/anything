#include "WorldGraphics.h"

WorldGraphics::WorldGraphics(void)
{
}

WorldGraphics::~WorldGraphics(void)
{
}

WorldGraphics::WorldGraphics(GameData& data)
{
	terrainImgList.resize(data.world.TERRAIN_LIST_SIZE);
	improvementImgList.resize(data.world.IMPROVEMENT_LIST_SIZE);
	unitImgList = std::vector<std::vector<sf::Image>>(data.world.UNIT_LIST_SIZE, std::vector<sf::Image>(5));

	loadResources();
}

void WorldGraphics::loadResources()
{
	sf::Image image;
	image.SetSmooth(false);
	std::string folder;

	//TODO should be able to define all of these based of World's object lists' image name values

	//terrain
	folder = "bin/graphics/terrain/";
	image.LoadFromFile(folder + "grass.png");
	terrainImgList[0] = image;
	image.LoadFromFile(folder + "sand.png");
	terrainImgList[2] = image;
	image.LoadFromFile(folder + "water.png");
	terrainImgList[3] = image;
	image.LoadFromFile(folder + "stone.png");
	terrainImgList[4] = image;
	
	//improvements
	folder = "bin/graphics/improvement/";
	image.LoadFromFile(folder + "tree.png");
	improvementImgList[0] = image;
	image.LoadFromFile(folder + "bush.png");
	improvementImgList[1] = image;
	image.LoadFromFile(folder + "boulder.png");
	improvementImgList[2] = image;
	image.LoadFromFile(folder + "wall.png");
	improvementImgList[3] = image;
	image.LoadFromFile(folder + "door.png");
	improvementImgList[4] = image;
	image.LoadFromFile(folder + "rubble.png");
	improvementImgList[5] = image;
	
	//units
	folder = "bin/graphics/unit/";
	image.LoadFromFile(folder + "playerS.png");
	unitImgList[0][0] = image;
	image.LoadFromFile(folder + "playerW.png");
	unitImgList[0][1] = image;
	image.LoadFromFile(folder + "playerN.png");
	unitImgList[0][2] = image;
	image.LoadFromFile(folder + "playerE.png");
	unitImgList[0][3] = image;
	image.LoadFromFile(folder + "playerS.png");
	unitImgList[0][4] = image;
	
	image.LoadFromFile(folder + "zombieS.png");
	unitImgList[1][0] = image;
	image.LoadFromFile(folder + "zombieS.png");
	unitImgList[1][1] = image;
	image.LoadFromFile(folder + "zombieS.png");
	unitImgList[1][2] = image;
	image.LoadFromFile(folder + "zombieS.png");
	unitImgList[1][3] = image;
	image.LoadFromFile(folder + "zombieS.png");
	unitImgList[1][4] = image;
	
	image.LoadFromFile(folder + "deerS.png");
	unitImgList[2][0] = image;
	image.LoadFromFile(folder + "deerS.png");
	unitImgList[2][1] = image;
	image.LoadFromFile(folder + "deerS.png");
	unitImgList[2][2] = image;
	image.LoadFromFile(folder + "deerS.png");
	unitImgList[2][3] = image;
	image.LoadFromFile(folder + "deerS.png");
	unitImgList[2][4] = image;
}

void WorldGraphics::drawWorld(sf::RenderWindow& mainWindow, GameData& data)
{
	int xOffset = (data.settings.WIN_WIDTH / 2) - (data.settings.TILE_SIZE * data.world.playerPos[0]) - data.settings.TILE_SIZE / 2;
	int yOffset = (data.settings.WIN_HEIGHT / 2) - (data.settings.TILE_SIZE * data.world.playerPos[1]) - data.settings.TILE_SIZE / 2;
	bool withinRangeX, withinRangeY;

	for (int i=0; i<data.world.WORLD_SIZE; i++)
	{
		for (int j=0; j<data.world.WORLD_SIZE; j++)
		{
			withinRangeX = i * data.settings.TILE_SIZE + data.settings.TILE_SIZE > -xOffset && i * data.settings.TILE_SIZE < -xOffset + data.settings.WIN_WIDTH;
			withinRangeY = j * data.settings.TILE_SIZE + data.settings.TILE_SIZE > -yOffset && j * data.settings.TILE_SIZE < -yOffset + data.settings.WIN_HEIGHT;

			if (withinRangeX && withinRangeY) //on screen
			{
				sf::Sprite sprite;
				sprite.SetX(i * data.settings.TILE_SIZE + xOffset);
				sprite.SetY(j * data.settings.TILE_SIZE + yOffset);

				sprite.SetImage(terrainImgList[data.world.getBoard()[i][j].getTerrain().ID]);
				sprite = scaleImage(sprite, data);
				mainWindow.Draw(sprite);

				if (data.world.getBoard()[i][j].hasImprovement)
				{
					sprite.SetImage(improvementImgList[data.world.getBoard()[i][j].getImprovement().ID]);
					sprite = scaleImage(sprite, data);
					mainWindow.Draw(sprite);
				}
				if (data.world.getBoard()[i][j].hasUnit)
				{
					sprite.SetImage(unitImgList[data.world.getBoard()[i][j].getUnit().ID][data.world.getBoard()[i][j].getUnit().direction]);
					sprite = scaleImage(sprite, data);
					mainWindow.Draw(sprite);
				}
			}
		}
	}
}

sf::Sprite WorldGraphics::scaleImage(sf::Sprite sprite, GameData& data)
{
	if(sprite.GetSize().x != data.settings.TILE_SIZE) //adjusts image to fit tile size
		sprite.Scale(data.settings.TILE_SIZE / sprite.GetSize().x, data.settings.TILE_SIZE / sprite.GetSize().y);
	return sprite;
}