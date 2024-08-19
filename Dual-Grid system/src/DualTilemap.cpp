#include "DualTilemap.h"

DualTilemap::DualTilemap()
{
	chosenTilePosition = sf::Vector2i(0, 0);
	tileSize = sf::Vector2f(16.f,16.f);
	textureTileSize = sf::Vector2i(16, 16);
	tileMapSize = sf::Vector2f(0.f, 0.f);

	initTileLayout();
	initPointer();
}

DualTilemap::DualTilemap(sf::Vector2u mapSize,sf::Vector2f tileSize, sf::Vector2i textureTileSize)
{
	chosenTilePosition = sf::Vector2i(0.f, 0.f);
	this->tileSize = tileSize;
	
	if (!(textureTileset.loadFromFile("Tilesets/Tileset.png")))
		std::cout << "Can't load tileset!" << std::endl;
	
	this->textureTileSize = textureTileSize;

	initTileLayout();
	initPointer();
	
	tilesId.resize(mapSize.x,std::vector<int>(mapSize.y,0));
	tilesDrawn.resize(mapSize.x+1, std::vector<Tile>(mapSize.y + 1));
	tileMapSize = sf::Vector2f(mapSize.x * tileSize.x, mapSize.y * tileSize.y);

	for(size_t i = 0; i < tilesDrawn.size(); i++)
	{
		for (size_t j = 0; j < tilesDrawn[i].size(); j++)
		{
			tilesDrawn[i][j] = Tile(tileSize, sf::Vector2f(i * tileSize.x, j * tileSize.y));
		}
	}
}

DualTilemap::~DualTilemap()
{

}

sf::Vector2i DualTilemap::getChosenTilePosition()
{
	return chosenTilePosition;
}

sf::Vector2f DualTilemap::getTileMapSize()
{
	return tileMapSize;
}

void DualTilemap::reset(sf::Vector2u mapSize, sf::Vector2f tileSize, sf::Vector2i textureTileSize)
{
	this->tileSize = tileSize;

	if (!(textureTileset.loadFromFile("Tilesets/Tileset.png")))
		std::cout << "Can't get tileset!" << std::endl;

	textureTileSize = sf::Vector2i(16, 16);

	initTileLayout();
	initPointer();

	tilesId.resize(mapSize.x, std::vector<int>(mapSize.y, 0));
	tilesDrawn.resize(mapSize.x + 1, std::vector<Tile>(mapSize.y + 1));
	tileMapSize = sf::Vector2f(mapSize.x * tileSize.x, mapSize.y * tileSize.y);

	for (size_t i = 0; i < tilesDrawn.size(); i++)
	{
		for (size_t j = 0; j < tilesDrawn[i].size(); j++)
		{
			tilesDrawn[i][j] = Tile(tileSize, sf::Vector2f(i * tileSize.x, j * tileSize.y));
		}
	}
}

void DualTilemap::addTile(const int x, const int y)
{
	if (x < tilesId.size() && x >= 0)
	{
		if (y < tilesId[x].size() && y >= 0)
		{
			if (tilesId[x][y] == 0)
			{
				tilesId[x][y] = 1;
				setTile(x, y);
			}
		}
	}
}


void DualTilemap::removeTile(const int x, const int y)
{
	if (x < tilesId.size() && x >= 0)
	{
		if (y < tilesId[x].size() && y >= 0)
		{
			if (tilesId[x][y] == 1)
			{
				tilesId[x][y] = 0;
				setTile(x, y);
			}
		}
	}
}

void DualTilemap::update(const sf::Vector2f& mouseViewPosition)
{
	chosenTilePosition = sf::Vector2i(
		static_cast<int>(std::floorf(mouseViewPosition.x / tileSize.x)),
		static_cast<int>(std::floorf(mouseViewPosition.y / tileSize.y))
	);
	
	pointer.setPosition(static_cast<float>(chosenTilePosition.x) * tileSize.x, static_cast<float>(chosenTilePosition.y) * tileSize.y);

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		addTile(static_cast<int>(chosenTilePosition.x), static_cast<int>(chosenTilePosition.y));
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		removeTile(static_cast<int>(chosenTilePosition.x), static_cast<int>(chosenTilePosition.y));
	}
}

void DualTilemap::render(sf::RenderTarget& target)
{
	for(auto & i : tilesDrawn)
	{
		for (auto& j : i)
		{
			if (j.getTexture() != nullptr && j.isLieInView(target.getView().getCenter()- target.getView().getSize()/2.f,target.getView().getSize()))
			{
				j.render(target);
			}
		}
	}
	target.draw(pointer);
}

void DualTilemap::setTile(const int& x, const int& y)
{
	for (auto& i : neighbours)
	{
		int xTile = std::get<0>(i) + x;
		int yTile = std::get<1>(i) + y;

		bool isCheckTileId[4]{ true,true,true,true };
		int checkTileId[4]{};
		if (xTile <= 0)
		{
			isCheckTileId[0] = false, isCheckTileId[2] = false;
		}
		if (xTile >= tilesId.size())
		{
			isCheckTileId[1] = false, isCheckTileId[3] = false;
		}
		if (yTile <= 0)
		{
			isCheckTileId[0] = false, isCheckTileId[1] = false;
		}
		if (yTile >= tilesId.size())
		{
			isCheckTileId[2] = false, isCheckTileId[3] = false;
		}

		if (isCheckTileId[0])
			checkTileId[0] = tilesId[xTile - 1][yTile - 1];
		if (isCheckTileId[1])
			checkTileId[1] = tilesId[xTile][yTile - 1];
		if (isCheckTileId[2])
			checkTileId[2] = tilesId[xTile - 1][yTile];
		if (isCheckTileId[3])
			checkTileId[3] = tilesId[xTile][yTile];

		sf::Vector2i texturePostion = tileLayout[std::tuple<int, int, int, int>
			(
				checkTileId[0],
				checkTileId[1],
				checkTileId[2],
				checkTileId[3]
			)
		];

		if (texturePostion == sf::Vector2i(0, 3))
		{
			tilesDrawn[xTile][yTile] = Tile(
				tileSize,
				sf::Vector2f(xTile * tileSize.x - tileSize.x / 2.f, yTile * tileSize.y - tileSize.y / 2.f)
			);
		}
		else
		{
			tilesDrawn[xTile][yTile] = Tile(
				tileSize,
				sf::Vector2f(xTile * tileSize.x - tileSize.x / 2.f, yTile * tileSize.y - tileSize.y / 2.f),
				&textureTileset,
				sf::Vector2i(textureTileSize.x * texturePostion.x, textureTileSize.y * texturePostion.y),
				textureTileSize
			);
		}
	}
}

void DualTilemap::initTileLayout()
{
	tileLayout[std::tuple<int, int, int, int>(1, 1, 1, 1)] = sf::Vector2i(2, 1);
	tileLayout[std::tuple<int, int, int, int>(0, 0, 0, 1)] = sf::Vector2i(1, 3);
	tileLayout[std::tuple<int, int, int, int>(0, 0, 1, 0)] = sf::Vector2i(0, 0);
	tileLayout[std::tuple<int, int, int, int>(0, 1, 0, 0)] = sf::Vector2i(0, 2);
	tileLayout[std::tuple<int, int, int, int>(1, 0, 0, 0)] = sf::Vector2i(3, 3);
	tileLayout[std::tuple<int, int, int, int>(0, 1, 0, 1)] = sf::Vector2i(1, 0);
	tileLayout[std::tuple<int, int, int, int>(1, 0, 1, 0)] = sf::Vector2i(3, 2);
	tileLayout[std::tuple<int, int, int, int>(0, 0, 1, 1)] = sf::Vector2i(3, 0);
	tileLayout[std::tuple<int, int, int, int>(1, 1, 0, 0)] = sf::Vector2i(1, 2);
	tileLayout[std::tuple<int, int, int, int>(0, 1, 1, 1)] = sf::Vector2i(1, 1);
	tileLayout[std::tuple<int, int, int, int>(1, 0, 1, 1)] = sf::Vector2i(2, 0);
	tileLayout[std::tuple<int, int, int, int>(1, 1, 0, 1)] = sf::Vector2i(2, 2);
	tileLayout[std::tuple<int, int, int, int>(1, 1, 1, 0)] = sf::Vector2i(3, 1);
	tileLayout[std::tuple<int, int, int, int>(0, 1, 1, 0)] = sf::Vector2i(2, 3);
	tileLayout[std::tuple<int, int, int, int>(1, 0, 0, 1)] = sf::Vector2i(0, 1);
	tileLayout[std::tuple<int, int, int, int>(0, 0, 0, 0)] = sf::Vector2i(0, 3);
}

void DualTilemap::initPointer()
{
	pointer.setSize(tileSize);
	pointer.setFillColor(sf::Color::Transparent);
	pointer.setOutlineColor(sf::Color(sf::Color::Green));
	pointer.setOutlineThickness(2.f);
}
