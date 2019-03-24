#include "agent.h"



agent::agent(unsigned int i, unsigned int x, unsigned int y, bool c, std::string s, unsigned int a)
{
	//Tempoary measure to test sign finding.
	objective = "FIND_DOOR";
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

std::pair<unsigned int, unsigned int> agent::getTarget()
{
	return target;
}

char agent::getSex()
{
	return 0;
}

std::string agent::getObjective()
{
	return objective;
}

std::pair<float, float> agent::getRposition()
{
	return rPosition;
}

bool agent::getCoperative()
{
	return false;
}

short agent::getIdleTime()
{
	return idleTime;
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

void agent::setTarget(unsigned int x, unsigned int y)
{
	target = std::make_pair(x, y);
}

void agent::setSex(char)
{
}

void agent::setObjective(std::string o)
{
	objective = o;
}

void agent::setRposition(float x, float y)
{
	rPosition = std::make_pair(x, y);
}

void agent::setCoperative(bool)
{
}

void agent::setIdleTime(short i)
{
	idleTime = i;
}
