#include "App.h"

App::App()
{
	initVariables();
	initWindow();
	initViews();
	initGridsAndTilemap();
	initInformationPanel();
}

App::~App()
{

}

void App::updateEvents()
{
	HandleEvents::instance.setMouseTicks(0.f);

	while (window.pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (sfEvent.type == sf::Event::MouseWheelScrolled)
		{
			HandleEvents::instance.setMouseTicks(sfEvent.mouseWheelScroll.delta);
		}
	}
}

void App::updateDeltaTime()
{
	dt = dtClock.restart().asSeconds();
}

void App::updateMousePosition()
{
	mousePositionWindow = sf::Mouse::getPosition(window);
	mousePositionView = window.mapPixelToCoords(mousePositionWindow);
}

void App::updateGridAndTilemap()
{
	if (isMovedView || isZoom)
	{
		for (auto& g : grids)
		{
			g.second.update(mainView.getSize(), mainView.getCenter() - (mainView.getSize() / 2.f), isZoom);
		}
	}

	tileMap.update(mousePositionView);
}


void App::updateView()
{
	isMovedView = false;
	isZoom = false;
	sf::Vector2f sizeView = mainView.getSize();

	//Moving
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (mainView.getCenter().x >= 0.f)
		{
			mainView.move(-viewSpeed * dt, 0.f);
			isMovedView = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (mainView.getCenter().x <= tileMap.getTileMapSize().x)
		{
			mainView.move(viewSpeed * dt, 0.f);
			isMovedView = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (mainView.getCenter().y >= 0.f)
		{
			mainView.move(0.f, -viewSpeed * dt);
			isMovedView = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (mainView.getCenter().y <= tileMap.getTileMapSize().y)
		{
			mainView.move(0.f, viewSpeed * dt);
			isMovedView = true;
		}
	}

	//Zooming
	if (HandleEvents::instance.getMouseTicks() > 0.f)
	{
		if (sizeView.x > minSizeView.x && sizeView.y > minSizeView.y)
		{
			mainView.zoom(0.5f);
			isZoom = true;
		}	
	}
	else if (HandleEvents::instance.getMouseTicks() < 0.f)	
	{
		if (sizeView.x < maxSizeView.x && sizeView.y < maxSizeView.y)
		{
			mainView.zoom(2.0f);
			isZoom = true;
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		mainView.setSize(window.getDefaultView().getSize());
		isZoom = true;

	}
}

void App::update()
{
	updateEvents();
	updateDeltaTime();
	updateMousePosition();
	updateGridAndTilemap();
	updateView();
	informationPanel.update(mousePositionView,tileMap.getChosenTilePosition(), mainView.getSize());
}

void App::render()
{
	window.clear();
	//-----------------------
	//Main View
	for (auto& g : grids)
	{
		window.draw(g.second);
	}
	tileMap.render(window);

	//Supplementary View
	window.setView(supplementaryView);
	informationPanel.render(window);

	window.setView(mainView);
	//-----------------------
	window.display();
}

void App::run()
{
	while(window.isOpen())
	{
		update();
		render();
	}
}

void App::initVariables()
{
	dt = 0.f;
	isZoom = false;
	isMovedView = false;
	if (!font.loadFromFile("Fonts/RPixerick.ttf"))
		std::cout << "Can't load font!" << std::endl;
}

void App::initWindow()
{
	window.create(sf::VideoMode(1280, 720), "Dual-Grid system", sf::Style::Default);
	window.setFramerateLimit(60);
}

void App::initViews()
{
	viewSpeed = SPEED_MOVEMENT_GRID;
	mainView.setSize(1280.f, 720.f);
	mainView.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

	supplementaryView.setSize(1280.f, 720.f);
	supplementaryView.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

	minSizeView = window.getDefaultView().getSize() * 0.2f;
	maxSizeView = window.getDefaultView().getSize() * 2.f;
}

void App::initGridsAndTilemap()
{
	//Grids
	tileSize = sf::Vector2f(32.f, 32.f);

	grids["MainGrid"] = Grid(mainView.getSize(), mainView.getCenter() - (mainView.getSize() / 2.f), tileSize);
	grids["DualGrid"] = Grid(mainView.getSize(), mainView.getCenter() - (mainView.getSize() / 2.f), tileSize, tileSize/2.f);
	grids["MainGrid"].setGridColor(sf::Color(73, 151, 230, 150));
	grids["DualGrid"].setGridColor(sf::Color(237, 78, 66, 150));

	//TileMap
	tileMap.reset(sf::Vector2u(100, 100), tileSize, sf::Vector2i(16,16));
}

void App::initInformationPanel()
{
	informationPanel.setPosition(sf::Vector2f(window.getSize().x - informationPanel.getSize().x - 50.f, 50.f));
	informationPanel.setFont(font);
}
