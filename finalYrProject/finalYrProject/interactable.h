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
	unsigned short getOrientation();
	std::pair<unsigned int, unsigned int> getDesination();

	//Setters.
	void setState(bool);
	void setOrientation(unsigned short);
	void makeSignDirection(unsigned int, unsigned int);

private:
	std::pair<unsigned int, unsigned int> location;
	std::pair<unsigned int, unsigned int> signDesination;
	std::string description;
	bool state;
	unsigned short integrity;
	unsigned short heatResistance;
	unsigned short oritentation;
	
};
#endif // !INTERACTABLE.H



