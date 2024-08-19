#ifndef INFORMATIONPANEL_H
#define INFORMATIONPANEL_H

#include "HandleEvents.h"

class InformationPanel
{
public:
	InformationPanel();
	virtual ~InformationPanel();

	sf::Vector2f getSize();

	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f panelPosition);

	void update(sf::Vector2f& mouseViewPositon, const sf::Vector2i& mouseGridPostion, const sf::Vector2f& viewSize);

	void render(sf::RenderTarget& target);
private:
	sf::RectangleShape shape;
	sf::Text text;
};

#endif // !INFORMATIONPANEL_H