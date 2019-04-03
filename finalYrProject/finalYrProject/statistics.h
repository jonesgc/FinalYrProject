#ifndef STATISTICS_H
#define STATISTICS_H

/*! \file statistics.h
	Author: Gregory Jones
	Version: N/A - work in progress.
	\breif Class header file. Work in progress - can be considered just a frame work.
*/

class statistics
{
public:
	statistics();
	~statistics();

	//Getters.
	unsigned int getInteractablesUsed();
	unsigned int getSimulationTimeElapsed();
	unsigned int getInteractionsBetweenAgents();

	//Due to the nature of the containers in this class, simple add functions are used to increment the variables, rather than traditional public setters.
	void addInteractableUsed();
	void addInteraction();


private:

	unsigned int interactablesUsed;
	unsigned int simulationTimeElapsed;
	unsigned int interactionsBetweenAgents;
};


#endif // !STATISTICS_H

