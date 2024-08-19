#ifndef TILE_H
#define TILE_H

#include "HandleEvents.h"

class Tile
{
public:
	Tile();
	Tile(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture = nullptr);
	Tile(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Vector2i textureTilePosition, sf::Vector2i textureTileSize);
	virtual ~Tile();
	
	bool isLieInView(sf::Vector2f topLeftPoint, sf::Vector2f viewSize) const;

	const sf::Texture* getTexture();

	void render(sf::RenderTarget& target);
private:
	sf::RectangleShape shape;
	
};

#endif // !TILE_H