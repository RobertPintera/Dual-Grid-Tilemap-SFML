#ifndef GRID_H
#define GRID_H

#include "HandleEvents.h"

class Grid : public sf::Drawable
{
public:
	Grid();
	Grid(sf::Vector2f viewSize, sf::Vector2f topLeftPoint, sf::Vector2f gridSize, sf::Vector2f gridOffSet = sf::Vector2f(0.f,0.f));
	virtual ~Grid();

	void setGridColor(sf::Color gridColor);

	void updateZoom(sf::Vector2f& viewSize);
	void update(sf::Vector2f viewSize, sf::Vector2f topLeftPoint, bool& isZoom);

private:
	sf::VertexArray vertices;

	sf::Vector2f topLeftDrawPoint;
	sf::Vector2f gridSize;
	sf::Vector2f gridOffSet;

	unsigned int xTiles;
	unsigned int yTiles;

	sf::Color colorGrid;

	void redrawGrid(sf::Vector2f& viewSize, sf::Vector2f& topLeftPoint, bool& isZoom);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // !GRID_H