#ifndef ENTITY_H
#define ENTITY_H

#include <utility>

class entity
{
public:
	entity();
	~entity();

	unsigned int getEnityID();
	std::pair<unsigned int, unsigned int> getPosition();
	
	void setPosition(unsigned int, unsigned int);
	void setEntityId(unsigned int);

	

private:
	unsigned int entityID;
	std::pair<unsigned int, unsigned int> position;
};

#endif // !ENTITY_H



