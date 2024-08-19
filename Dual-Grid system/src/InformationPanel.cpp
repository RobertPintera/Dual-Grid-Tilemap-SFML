#include "InformationPanel.h"

InformationPanel::InformationPanel()
{
	shape.setSize(sf::Vector2f(600.f, 160.f));
	shape.setPosition(0.f,0.f);
	shape.setFillColor(sf::Color(255, 255, 255, 180));

	text.setCharacterSize(32);
	text.setPosition(sf::Vector2f(20.f, 20.f));
	text.setFillColor(sf::Color::Black);
}

InformationPanel::~InformationPanel()
{

}

sf::Vector2f InformationPanel::getSize()
{
	return shape.getSize();
}

void InformationPanel::setFont(sf::Font& font)
{
	text.setFont(font);
}

void InformationPanel::setPosition(sf::Vector2f panelPosition)
{
	shape.setPosition(panelPosition);
	text.setPosition(panelPosition + sf::Vector2f(20.f,20.f));

}

void InformationPanel::update(sf::Vector2f& mouseViewPositon, const sf::Vector2i& mouseGridPostion, const sf::Vector2f& viewSize)
{
	std::string content =
		"Mouse View Position: (" +
		std::to_string(mouseViewPositon.x) + ';' + ' ' +
		std::to_string(mouseViewPositon.y) + ')' +
		'\n' +
		"Point Tile Position: (" +
		std::to_string(mouseGridPostion.x) + ';' + ' ' +
		std::to_string(mouseGridPostion.y) + ')' +
		'\n' +
		"View Size: (" +
		std::to_string(viewSize.x) + ';' + ' ' +
		std::to_string(viewSize.y) + ')';
	 text.setString(content);
}

void InformationPanel::render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}
