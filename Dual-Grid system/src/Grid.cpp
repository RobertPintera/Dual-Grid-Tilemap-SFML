#include "Grid.h"

Grid::Grid(): 
	gridSize(sf::Vector2f(16.f,16.f)), gridOffSet(sf::Vector2f(0.f,0.f)), colorGrid(sf::Color(255, 255, 255, 255)), 
	xTiles(0), yTiles(0), vertices(sf::Lines), topLeftDrawPoint(sf::Vector2f(0.f,0.f))
{

}

Grid::Grid(sf::Vector2f viewSize, sf::Vector2f topLeftPoint, sf::Vector2f gridSize, sf::Vector2f gridOffSet):
	gridSize(gridSize),gridOffSet(gridOffSet),colorGrid(sf::Color(255, 255, 255, 255)),
	xTiles(static_cast<unsigned int>((viewSize.x / gridSize.x) + 2.f) + 1), 
	yTiles(static_cast<unsigned int>((viewSize.y / gridSize.y) + 2.f) + 1), 
	vertices(sf::Lines), topLeftDrawPoint(topLeftPoint)
{
	redrawGrid(viewSize, topLeftPoint, true);
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

void Grid::update(sf::Vector2f viewSize, sf::Vector2f topLeftPoint, bool& isZoom)
{
	redrawGrid(viewSize, topLeftPoint, isZoom);
}

void Grid::redrawGrid(sf::Vector2f& viewSize, sf::Vector2f& topLeftPoint, bool isZoom)
{
	topLeftDrawPoint = topLeftPoint;
	float remainderX = std::fmod(topLeftPoint.x, gridSize.x);
	float remainderY = std::fmod(topLeftPoint.y, gridSize.y);

	if (remainderX != 0.f)
	{
		topLeftDrawPoint.x = std::floorf(topLeftPoint.x - static_cast<float>(remainderX));
	}

	if (remainderY != 0.f)
	{
		topLeftDrawPoint.y = std::floorf(topLeftPoint.y - static_cast<float>(remainderY));
	}

	if (isZoom)
		updateZoom(viewSize);

	for (size_t i = 0; i < xTiles; i++)
	{
		sf::Vertex* line = &vertices[i * 2];
		line[0].position = sf::Vector2f
		(
			topLeftDrawPoint.x + i * gridSize.x - gridSize.x + gridOffSet.x,
			topLeftPoint.y
		);
		line[0].color = colorGrid;
		line[1].position = sf::Vector2f
		(
			topLeftDrawPoint.x + i * gridSize.x - gridSize.x + gridOffSet.x,
			topLeftPoint.y + viewSize.y
		);
		line[1].color = colorGrid;
		line = nullptr;
	}

	for (size_t i = 0; i < yTiles; i++)
	{
		sf::Vertex* line = &vertices[xTiles * 2 + i * 2];
		line[0].position = sf::Vector2f
		(
			topLeftPoint.x,
			topLeftDrawPoint.y + i * gridSize.y - gridSize.y + gridOffSet.y);
		line[0].color = colorGrid;
		line[1].position = sf::Vector2f
		(
			topLeftPoint.x + viewSize.x,
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
