#ifndef CROWD_H
#define CROWD_H

/*! \file crowd.h
	Author: Gregory Jones
	Version: N/A - work in progress.
	\breif Class header file. Work in progress - can be considered just a frame work.
*/

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


