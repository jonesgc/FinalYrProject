#include "agent.h"



agent::agent(unsigned int i, unsigned int x, unsigned int y, bool c, std::string s, unsigned int a)
{
	setEntityId(i);
	setPosition(x, y);
	coperative = c;
	sex = s;
	age = a;
}


agent::~agent()
{
}

unsigned short agent::getAge()
{
	return 0;
}

unsigned short agent::getHealth()
{
	return 0;
}

unsigned short agent::getEnergy()
{
	return 0;
}

unsigned short agent::getStress()
{
	return 0;
}

unsigned int agent::getTarget()
{
	return 0;
}

char agent::getSex()
{
	return 0;
}

std::string agent::getObjective()
{
	return std::string();
}

std::pair<float, float> agent::getRposition()
{
	return rPosition;
}

bool agent::getCoperative()
{
	return false;
}

void agent::setAge(unsigned short)
{
}

void agent::setHealth(unsigned short)
{
}

void agent::setEnergy(unsigned short)
{
}

void agent::setTarget(unsigned int)
{
}

void agent::setSex(char)
{
}

void agent::setObjective(std::string)
{
}

void agent::setRposition(float x, float y)
{
	rPosition = std::make_pair(x, y);
}

void agent::setCoperative(bool)
{
}
