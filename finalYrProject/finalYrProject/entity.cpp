#include "entity.h"



entity::entity()
{
}


entity::~entity()
{
}

unsigned int entity::getEnityID()
{
	return entityID;
}

void entity::setEntityId(unsigned int i)
{
	entityID = i;
}

std::pair<unsigned int, unsigned int> entity::getPosition()
{
	return position;
}

void entity::setPosition(unsigned int x, unsigned int y)
{
	position = std::make_pair(x, y);
}

