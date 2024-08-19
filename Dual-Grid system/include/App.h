#ifndef APP_H
#define APP_H

#define SPEED_MOVEMENT_GRID 400.f

#include "InformationPanel.h"
#include "Grid.h"
#include "DualTilemap.h"
#include "memory"

class App
{
public:
	App();
	virtual ~App();

	void updateEvents();
	void updateDeltaTime();
	void updateMousePosition();
	void updateGridAndTilemap();
	void updateView();
	void update();

	void render();

	void run();

private:
	sf::RenderWindow window;
	sf::Event sfEvent;

	sf::Font font;
	
	//View variables
	sf::View mainView;
	sf::View supplementaryView;
	sf::Vector2f minSizeView;
	sf::Vector2f maxSizeView;
	float viewSpeed;
	bool isZoom;
	bool isMovedView;

	//Mouse Positions
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;

	//Delta Time
	sf::Clock dtClock;
	float dt;

	//Tilemap variables
	InformationPanel informationPanel;
	sf::Vector2f tileSize;
	std::map<std::string, Grid> grids;
	DualTilemap tileMap;

	//Initializers
	void initVariables();
	void initWindow();
	void initViews();
	void initGridsAndTilemap();
	void initInformationPanel();
};

#endif // !APP_H