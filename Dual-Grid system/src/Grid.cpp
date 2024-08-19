#include "Grid.h"

Grid::Grid():
	gridSize(sf::Vector2f(16.f,16.f)), gridOffSet(sf::Vector2f(0.f,0.f)), colorGrid(sf::Color(255, 255, 255, 255))
{
	vertices.setPrimitiveType(sf::Lines);
	xTiles = 0;
	yTiles = 0;
}

Grid::Grid(sf::Vector2f viewSize, sf::Vector2f topLeftPoint, sf::Vector2f gridSize, sf::Vector2f gridOffSet):
	gridSize(gridSize),gridOffSet(gridOffSet),colorGrid(sf::Color(255, 255, 255, 255))
{
	vertices.setPrimitiveType(sf::Lines);
	bool isZoom = true;

	redrawGrid(viewSize, topLeftPoint, isZoom);
}

Grid::~Grid()
{
}

void Grid::setGridColor(sf::Color colorGrid)
{
	this->colorGrid = colorGrid;

	for (size_t i = 0; i < xTiles; i++)
	{
		sf::Vertex* line = &vertices[i * 2];
		line[0].color = colorGrid;
		line[1].color = colorGrid;
		line = nullptr;
	}

	for (size_t i = 0; i < yTiles; i++)
	{
		sf::Vertex* line = &vertices[xTiles * 2 + i * 2];
		line[0].color = colorGrid;
		line[1].color = colorGrid;
		line = nullptr;
	}
}

void Grid::updateZoom(sf::Vector2f& viewSize)
{
	xTiles = static_cast<unsigned int>((viewSize.x / gridSize.x) + 2.f) + 1;
	yTiles = static_cast<unsigned int>((viewSize.y / gridSize.y) + 2.f) + 1;

	unsigned int numberTiles = xTiles * 2 + yTiles * 2;
	vertices.resize(numberTiles);
}

void Grid::update(sf::Vector2f viewSize, sf::Vector2f topLeftpoint, bool& isZoom)
{
	redrawGrid(viewSize,topLeftpoint,isZoom);
}

void Grid::redrawGrid(sf::Vector2f& viewSize, sf::Vector2f& topLeftpoint, bool& isZoom)
{
	topLeftDrawPoint = topLeftpoint;
	float remainderX = std::fmod(topLeftpoint.x, gridSize.x);
	float remainderY = std::fmod(topLeftpoint.y, gridSize.y);

	if (remainderX != 0.f)
	{
		topLeftDrawPoint.x = std::floorf(topLeftpoint.x - static_cast<float>(remainderX));
	}

	if (remainderY != 0.f)
	{
		topLeftDrawPoint.y = std::floorf(topLeftpoint.y - static_cast<float>(remainderY));
	}

	if (isZoom)
		updateZoom(viewSize);

	for (size_t i = 0; i < xTiles; i++)
	{
		sf::Vertex* line = &vertices[i * 2];
		line[0].position = sf::Vector2f
		(
			topLeftDrawPoint.x + i * gridSize.x - gridSize.x + gridOffSet.x, 
			topLeftpoint.y
		);
		line[0].color = colorGrid;
		line[1].position = sf::Vector2f
		(
			topLeftDrawPoint.x + i * gridSize.x - gridSize.x + gridOffSet.x, 
			topLeftpoint.y + viewSize.y
		);
		line[1].color = colorGrid;
		line = nullptr;
	}

	for (size_t i = 0; i < yTiles; i++)
	{
		sf::Vertex* line = &vertices[xTiles * 2 + i * 2];
		line[0].position = sf::Vector2f
		(
			topLeftpoint.x, 
			topLeftDrawPoint.y + i * gridSize.y - gridSize.y + gridOffSet.y);
		line[0].color = colorGrid;
		line[1].position = sf::Vector2f
		(
			topLeftpoint.x + viewSize.x, 
			topLeftDrawPoint.y + i * gridSize.y - gridSize.y + gridOffSet.y
		);
		line[1].color = colorGrid;
		line = nullptr;
	}
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(vertices, states);
}
