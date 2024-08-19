#ifndef HANDLEEVENTS_H
#define HANDLEEVENTS_H

#include "SFML/Graphics.hpp"
#include "iostream"

class HandleEvents
{
public:
	static HandleEvents instance;
	
	float getMouseTicks();

	void setMouseTicks(float mouseTicks);
private:
	HandleEvents();
	virtual ~HandleEvents();

	float mouseTicks;
};

#endif // !HANDLEEVENTS_H
