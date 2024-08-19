#include "HandleEvents.h"

HandleEvents HandleEvents::instance;

float HandleEvents::getMouseTicks()
{
	return mouseTicks;
}

void HandleEvents::setMouseTicks(float mouseTicks)
{
	this->mouseTicks = mouseTicks;
}


HandleEvents::HandleEvents()
{
	mouseTicks = 0;
}

HandleEvents::~HandleEvents()
{
}
