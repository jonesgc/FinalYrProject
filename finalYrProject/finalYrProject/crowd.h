#ifndef CROWD_H
#define CROWD_H

#include <vector>
#include <string>

#include "agent.h"

class crowd
{
public:
	crowd();
	~crowd();

	//Getters.
	unsigned short getCrowdID();
	std::vector<agent> getCrowdMembers();
	std::string getCrowdObjective();

private:

	unsigned short crowdID;
	std::vector<agent> crowdMembers;
	std::string crowdObjective;
	
};

#endif // !CROWD_H


