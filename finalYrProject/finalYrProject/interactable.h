#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "entity.h"
#include <string>

class interactable : public entity
{
public:
	interactable(unsigned int, unsigned int, unsigned int, std::string, bool, unsigned short, unsigned short);
	~interactable();

	//Getters.
	std::string getDescription();
	bool getState();
	unsigned short getIntegrity();
	unsigned short getHeatResistance();

	//Setters.
	void setState(bool);

private:
	std::pair<unsigned int, unsigned int> location;
	std::string description;
	bool state;
	unsigned short integrity;
	unsigned short heatResistance;

	
};
#endif // !INTERACTABLE.H



