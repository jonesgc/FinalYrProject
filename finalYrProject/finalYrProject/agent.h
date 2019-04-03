#ifndef AGENT_H
#define AGENT_H

/*!
	\file agent.h
	Author: Gregory Jones
	Version: 0.1
	\brief Class header file. This file contains mostly getters and setters for an agent, the constructor is the most important element of this class.
*/
#include "entity.h"
#include <string>
#include <utility>


class agent : public entity
{
public:
	agent(unsigned int, unsigned int, unsigned int, bool, std::string, unsigned int);
	~agent();

	//Getters.
	unsigned short getAge();
	unsigned short getHealth();
	unsigned short getEnergy();
	unsigned short getStress();
	std::pair<unsigned int, unsigned int> getTarget();
	char getSex();
	std::string getObjective();
	std::pair<float, float> getRposition();
	bool getCoperative();
	short getIdleTime();

	//Setters.
	void setAge(unsigned short);
	void setHealth(unsigned short);
	void setEnergy(unsigned short);
	void setTarget(unsigned int, unsigned int);
	void setSex(char);
	void setObjective(std::string);
	void setRposition(float, float);
	void setCoperative(bool);
	void setIdleTime(short);

private:
	unsigned short age;
	unsigned short health;
	unsigned short energy;
	unsigned short stress;
	std::pair<unsigned int, unsigned int> target;
	std::string sex;
	std::string objective;
	std::pair<float, float> rPosition;
	bool coperative;
	short idleTime;
};


#endif // !AGENT_H


