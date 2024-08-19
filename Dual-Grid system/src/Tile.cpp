#include "Tile.h"


Tile::Tile()
{

}

Tile::Tile(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture)
{
	shape.setSize(size);
	shape.setPosition(position);
	if (texture != nullptr)
	{
		shape.setTexture(texture);
	}
}

Tile::Tile(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Vector2i textureTilePosition, sf::Vector2i textureTileSize)
{
	shape.setSize(size);
	shape.setPosition(position);
	shape.setTexture(texture,true);
	shape.setTextureRect(
		sf::IntRect(
			textureTilePosition.x, textureTilePosition.y,
			textureTileSize.x, textureTileSize.y
		)
	);
}

Tile::~Tile()
{
}

bool Tile::isLieInView(sf::Vector2f topLeftPoint, sf::Vector2f viewSize) const
{
	if (topLeftPoint.x - shape.getSize().x > shape.getPosition().x ||
		topLeftPoint.x + viewSize.x + shape.getSize().x < shape.getPosition().x || 
		topLeftPoint.y - shape.getSize().y > shape.getPosition().y ||
		topLeftPoint.y + viewSize.y + shape.getSize().y < shape.getPosition().y)
	{
		return false;
	}
	return true;
}

const sf::Texture* Tile::getTexture()
{
	return shape.getTexture();
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}

