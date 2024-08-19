#ifndef DUALTILEMAP_H
#define DUALTILEMAP_H

#include "Tile.h"

class DualTilemap
{
public:
	DualTilemap();
	DualTilemap(sf::Vector2u mapSize, sf::Vector2f tileSize, sf::Vector2i textureTileSize);
	virtual ~DualTilemap();

	sf::Vector2i getChosenTilePosition();
	sf::Vector2f getTileMapSize();

	void reset(sf::Vector2u mapSize, sf::Vector2f tileSize, sf::Vector2i textureTileSize);

	void addTile(const int x, const int y);
	void removeTile(const int x, const int y);

	void update(const sf::Vector2f& mouseViewPosition);
	void render(sf::RenderTarget& target);

private:
	sf::Vector2f tileSize;
	sf::Vector2f tileMapSize;

	sf::RectangleShape pointer;
	sf::Vector2i chosenTilePosition;
	
	sf::Texture textureTileset;
	sf::Vector2i textureTileSize;

	std::map<std::tuple<int, int, int, int>, sf::Vector2i> tileLayout;
	std::tuple<int, int> neighbours[4] = { std::tuple<int,int>(0,0),std::tuple<int,int>(1,0), std::tuple<int,int>(0,1),std::tuple<int,int>(1,1) };

	std::vector<std::vector<int>> tilesId;
	std::vector<std::vector<Tile>> tilesDrawn;
	
	void setTile(const int& x, const int& y);
	
	void initTileLayout();
	void initPointer();
};

#endif // !DUALTILEMAP_H