#include "World.h"

World::World(void)
{
	board = std::vector<std::vector<Tile>>(WORLD_SIZE, std::vector<Tile>(WORLD_SIZE));
	playerPos.resize(2);

	//define vector sizes
	terrainList.resize(TERRAIN_LIST_SIZE);
	improvementList.resize(IMPROVEMENT_LIST_SIZE);
	unitList.resize(UNIT_LIST_SIZE);

	heightMapImage.SetSmooth(false);

	initializeTiles(); //define tile IDs
}

World::~World(void)
{
}

std::vector<std::vector<Tile>>& World::getBoard()
{
	return board;
}

void World::newGame()
{
	time = 0;
	playerPos[0] = WORLD_SIZE*3/8;
	playerPos[1] = WORLD_SIZE*3/8;

	heightMap = std::vector<std::vector<int>>(WORLD_SIZE, std::vector<int>(WORLD_SIZE, -10000));

	//seeding heightMap
	heightMap[WORLD_SIZE / 2][WORLD_SIZE / 2] = 254; //mid
	heightMap[WORLD_SIZE / 2][0] = 0; //top
	heightMap[0][WORLD_SIZE / 2] = 0; //left
	heightMap[WORLD_SIZE-1][WORLD_SIZE / 2] = 0; //right
	heightMap[WORLD_SIZE / 2][WORLD_SIZE-1] = 0; //bottom
	std::vector<int> seed(4, 0);
	//seed[1] = 254;
	//seed[3] = 254;

	calculateHeightMap(62, seed);

	//fill world with tiles
	for (int i=0; i<WORLD_SIZE; i++)
	{
		for (int j=0; j<WORLD_SIZE; j++)
		{
			if (playerPos[0] == i && playerPos[1] == j) //adds player
			{
				board[i][j] = Tile(i, j, terrainList[0]);
				board[i][j].addUnit(unitList[0]);
			}
			else
			{
				if (heightMap[i][j] > 169) //mountain
					board[i][j] = Tile(i, j, terrainList[4]);
				else if (heightMap[i][j] > 84) //land
				{
					board[i][j] = Tile(i, j, terrainList[0]);

					if (rand() % 30 < 1) // 1 in 30 chance of bush
						board[i][j].addImprovement(improvementList[1]);
					else if (rand() % 25 < 1) // 1 in 25 chance of tree
						board[i][j].addImprovement(improvementList[0]);
				}
				else //water
					board[i][j] = Tile(i, j, terrainList[3]);
			}
		}
	}

	createHeightMapImage();
}

void World::initializeTiles()
{
	//terrain
	terrainList[0] = Terrain(0, "Grass", "grass.png", true, false, true);
	terrainList[1] = Terrain(1, "Rubble", "rubble.png", true, false, true);
	terrainList[2] = Terrain(2, "Sand", "sand.png", true, true, true);
	terrainList[3] = Terrain(3, "Water", "water.png", false, true, true);
	terrainList[4] = Terrain(4, "Stone", "stone.png", false, false, false);

	//improvements
	improvementList[0] = Improvement(0, "Tree", "tree.png", false, false, true);
	improvementList[1] = Improvement(1, "Bush", "bush.png", true, true, false);
	improvementList[2] = Improvement(2, "Boulder", "boulder.png", false, false, true);
	improvementList[3] = Improvement(3, "Wall", "wall.png", false, false, true);
	improvementList[4] = Improvement(4, "Door", "door.png", true, false, true);

	//units
	std::vector<std::string> unitImageList;
	unitImageList.resize(4);

	fillUnitImageList(unitImageList, "player");
	unitList[0] = Unit(0, "Player", unitImageList, "playerCorpse.png", 100, 100, 100, 100, 100, 100, 0, 1, false, true);
	fillUnitImageList(unitImageList, "zombie");
	unitList[1] = Unit(1, "Zombie", unitImageList, "zombieCorpse.png", 100, 100, 100, 100, 100, 100, 0, 1, false, false);
	fillUnitImageList(unitImageList, "deer");
	unitList[2] = Unit(2, "Deer", unitImageList, "deerCorpse.png", 100, 100, 100, 100, 100, 100, 0, 1, true, false);
}

void World::fillUnitImageList(std::vector<std::string>& unitImageList, std::string name)
{
	sf::Image testImage;

	unitImageList[0] = name + "S.png";

	if (testImage.LoadFromFile("bin/graphics/unit/" + name + "W.png")) //image exists
		unitImageList[1] = name + "W.png";
	else
		unitImageList[1] = name + "S.png";

	if (testImage.LoadFromFile("bin/graphics/unit/" + name + "N.png")) //image exists
		unitImageList[2] = name + "N.png";
	else
		unitImageList[2] = name + "S.png";

	if (testImage.LoadFromFile("bin/graphics/unit/" + name + "E.png")) //image exists
		unitImageList[3] = name + "E.png";
	else
		unitImageList[3] = name + "S.png";
	
	if (testImage.LoadFromFile("bin/graphics/unit/" + name + "Corpse.png")) //image exists
		unitImageList[3] = name + "Corpse.png";
	else
		unitImageList[3] = name + "S.png";
}

void World::moveUnit(int oldX, int oldY, int newX, int newY)
{
	board[newX][newY].addUnit(board[oldX][oldY].getUnit());
	board[oldX][oldY].removeUnit();
}

void World::addUnit(int ID, int x, int y)
{
	board[x][y].addUnit(unitList[ID]);
}

Unit& World::getPlayer()
{
	return board[playerPos[0]][playerPos[1]].getUnit();
}

bool World::isPlayerFacingTile()
{
	int x = playerPos[0];
	int y = playerPos[1];

	switch (getPlayer().direction)
	{
		case 0:
			y++;
			break;
		case 1:
			x--;
			break;
		case 2:
			y--;
			break;
		case 3:
			x++;
			break;
	}

	if (x >= 0 && x < WORLD_SIZE && y >= 0 && y < WORLD_SIZE)
		return true;
	return false;
}

Tile World::getPlayerFacedTile()
{
	int x = playerPos[0];
	int y = playerPos[1];

	switch (getPlayer().direction)
	{
		case 0:
			y++;
			break;
		case 1:
			x--;
			break;
		case 2:
			y--;
			break;
		case 3:
			x++;
			break;
	}

	return board[x][y];
}

void World::createHeightMapImage()
{
	sf::Image image;
	sf::Color color;
	int height;

	image.Create(WORLD_SIZE, WORLD_SIZE, sf::Color::White);

	for (int i=0; i<WORLD_SIZE; i++)
	{
		for (int j=0; j<WORLD_SIZE; j++)
		{
			height = heightMap[i][j];
			if (height > 254)
				height = 254;
			else if (height < 0)
				height = 0;
			image.SetPixel(i, j, sf::Color(height, height, height, 255));
		}
	}

	heightMapImage = image;
}

void World::calculateHeightMap(int variance)
{
	heightMap[0][0] = rand() % 255;
	heightMap[WORLD_SIZE-1][0] = rand() % 255;
	heightMap[0][WORLD_SIZE-1] = rand() % 255;
	heightMap[WORLD_SIZE-1][WORLD_SIZE-1] = rand() % 255;

	std::vector<int> topLeft(2);
	std::vector<int> topRight(2);
	std::vector<int> bottomLeft(2);
	std::vector<int> bottomRight(2);

	topLeft[0] = 0;
	topLeft[1] = 0;
	topRight[0] = WORLD_SIZE-1;
	topRight[1] = 0;
	bottomLeft[0] = 0;
	bottomLeft[1] = WORLD_SIZE-1;
	bottomRight[0] = WORLD_SIZE-1;
	bottomRight[1] = WORLD_SIZE-1;
	
	calculateHeightMap(topLeft, topRight, bottomLeft, bottomRight, variance);
}

void World::calculateHeightMap(int variance, std::vector<int> seed)
{
	heightMap[0][0] = seed[0];
	heightMap[WORLD_SIZE-1][0] = seed[1];
	heightMap[0][WORLD_SIZE-1] = seed[2];
	heightMap[WORLD_SIZE-1][WORLD_SIZE-1] = seed[3];

	std::vector<int> topLeft(2);
	std::vector<int> topRight(2);
	std::vector<int> bottomLeft(2);
	std::vector<int> bottomRight(2);

	topLeft[0] = 0;
	topLeft[1] = 0;
	topRight[0] = WORLD_SIZE-1;
	topRight[1] = 0;
	bottomLeft[0] = 0;
	bottomLeft[1] = WORLD_SIZE-1;
	bottomRight[0] = WORLD_SIZE-1;
	bottomRight[1] = WORLD_SIZE-1;
	
	calculateHeightMap(topLeft, topRight, bottomLeft, bottomRight, variance);
}

void World::calculateHeightMap(std::vector<int> topLeft, std::vector<int> topRight, std::vector<int> bottomLeft, std::vector<int> bottomRight, int variance)
{
	if ((static_cast<float>(bottomRight[0]) - topLeft[0]) / 2 >= 1)
	{
		std::vector<int> mid(2);
		std::vector<int> top(2);
		std::vector<int> left(2);
		std::vector<int> right(2);
		std::vector<int> bottom(2);
		
		mid[0] = topLeft[0] + (bottomRight[0] - topLeft[0]) / 2;
		mid[1] = topLeft[1] + (bottomRight[1] - topLeft[1]) / 2;
		top[0] = topLeft[0] + (topRight[0] - topLeft[0]) / 2;
		top[1] = topLeft[1];
		left[0] = topLeft[0];
		left[1] = topLeft[1] + (bottomLeft[1] - topLeft[1]) / 2;
		right[0] = topRight[0];
		right[1] = topRight[1] + (bottomRight[1] - topRight[1]) / 2;
		bottom[0] = bottomLeft[0] + (bottomRight[0] - bottomLeft[0]) / 2;
		bottom[1] = bottomLeft[1];

		//square
		if (heightMap[mid[0]][mid[1]] == -10000)
			heightMap[mid[0]][mid[1]] = (heightMap[topLeft[0]][topLeft[1]] + heightMap[topRight[0]][topRight[1]] + heightMap[bottomLeft[0]][bottomLeft[1]] + heightMap[bottomRight[0]][bottomRight[1]]) / 4 + rand() % variance - variance / 2;

		//diamond
		if (heightMap[top[0]][top[1]] == -10000) //top
		{
			if (top[1] - 1 < 0)
				heightMap[top[0]][top[1]] = (heightMap[topLeft[0]][topLeft[1]] + heightMap[topRight[0]][topRight[1]] + heightMap[mid[0]][mid[1]]) / 3 + rand() % variance - variance / 2;
			else
				heightMap[top[0]][top[1]] = (heightMap[topLeft[0]][topLeft[1]] + heightMap[topRight[0]][topRight[1]] + heightMap[mid[0]][mid[1]] + heightMap[top[0]][top[1]-1]*5) / 8 + rand() % variance - variance / 2;
		}
		if (heightMap[left[0]][left[1]] == -10000) //left
		{
			if (left[0] - 1 < 0)
				heightMap[left[0]][left[1]] = (heightMap[topLeft[0]][topLeft[1]] + heightMap[bottomLeft[0]][bottomLeft[1]] + heightMap[mid[0]][mid[1]]) / 3 + rand() % variance - variance / 2;
			else
				heightMap[left[0]][left[1]] = (heightMap[topLeft[0]][topLeft[1]] + heightMap[bottomLeft[0]][bottomLeft[1]] + heightMap[mid[0]][mid[1]] + heightMap[left[0]-1][left[1]]*5) / 8 + rand() % variance - variance / 2;
		}
		if (heightMap[right[0]][right[1]] == -10000) //right
			heightMap[right[0]][right[1]] = (heightMap[topRight[0]][topRight[1]] + heightMap[bottomRight[0]][bottomRight[1]] + heightMap[mid[0]][mid[1]]) / 3 + rand() % variance - variance / 2;
		if (heightMap[bottom[0]][bottom[1]] == -10000) //bottom
			heightMap[bottom[0]][bottom[1]] = (heightMap[bottomLeft[0]][bottomLeft[1]] + heightMap[bottomRight[0]][bottomRight[1]] + heightMap[mid[0]][mid[1]]) / 3 + rand() % variance - variance / 2;

		calculateHeightMap(topLeft, top, left, mid, ceil(variance*.9));
		calculateHeightMap(top, topRight, mid, right, ceil(variance*.9));
		calculateHeightMap(left, mid, bottomLeft, bottom, ceil(variance*.9));
		calculateHeightMap(mid, right, bottom, bottomRight, ceil(variance*.9));
	}
}