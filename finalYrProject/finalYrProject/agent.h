#ifndef AGENT_H
#define AGENT_H

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
	unsigned int getTarget();
	char getSex();
	std::string getObjective();
	std::pair<float, float> getRposition();
	bool getCoperative();

	//Setters.
	void setAge(unsigned short);
	void setHealth(unsigned short);
	void setEnergy(unsigned short);
	void setTarget(unsigned int);
	void setSex(char);
	void setObjective(std::string);
	void setRposition(float, float);
	void setCoperative(bool);

private:
	unsigned short age;
	unsigned short health;
	unsigned short energy;
	unsigned short stress;
	unsigned int target;
	std::string sex;
	std::string objective;
	std::pair<float, float> rPosition;
	bool coperative;
};


#endif // !AGENT_H


