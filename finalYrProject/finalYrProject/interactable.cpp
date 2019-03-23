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

interactable::interactable()
{

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

unsigned short interactable::getOrientation()
{
	return oritentation;
}

std::pair<unsigned int, unsigned int> interactable::getDesination()
{
	return signDesination;
}

void interactable::setState(bool s)
{
	state = s;
}

void interactable::setOrientation(unsigned short o)
{
	oritentation = o;
}

void interactable::makeSignDirection(unsigned int x, unsigned int y)
{
	signDesination = std::make_pair(x, y);
}
