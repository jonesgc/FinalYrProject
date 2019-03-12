#include "interactable.h"




interactable::interactable(unsigned int id,unsigned int x, unsigned int y, std::string d, bool s, unsigned short i, unsigned short hr)
{
	setEntityId(id);
	setPosition(x, y);
	description = d;
	state = s;
	integrity = i;
	heatResistance = hr;
}

interactable::~interactable()
{
}

std::string interactable::getDescription()
{
	return description;
}

bool interactable::getState()
{
	return state;
}

unsigned short interactable::getIntegrity()
{
	return integrity;
}

unsigned short interactable::getHeatResistance()
{
	return heatResistance;
}

void interactable::setState(bool s)
{
	state = s;
}
