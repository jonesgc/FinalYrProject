#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

/*! \file environment.h
Author: Gregory Jones
Version: 0.1
\brief  Class header file. Environment object that contains the grid that the agents will move within and the interactable entities.
*/


#include"SFML/Graphics.hpp"

#include <utility>
#include <vector>

class Environment
{
public:
	Environment();
	Environment(unsigned int, unsigned int);
	~Environment();
	
	std::pair<unsigned int, unsigned int> getHazardEmitterLoc();
	unsigned short getHazardSpeed();
	std::vector<std::vector<unsigned int>> getEnvironmentGrid();
	sf::VertexArray getRenderedGrid();
	std::pair<unsigned int, unsigned int> getGridSize();
	sf::VertexArray getRenderedInter();

	void setHazardSpeed(unsigned short);
	void setHazardEmitterLoc(unsigned int, unsigned int);
	void setRenderedGrid(sf::VertexArray);
	void setRenderedInter(sf::VertexArray);


	/*
	\fn void changeTile(unsigned int, unsigned int, unsigned short);
	\brief This function will allow a "tile" value to be changed. This is priamrily used in movement of agents.
	\param x coordinate of the tile to be changed.
	\param y coordinate of the tile to be changed.
	\param The code of which to change the tile value to.
	*/
	void changeTile(unsigned int, unsigned int, unsigned short);

private:
	std::pair<unsigned int, unsigned int> hazardEmitter;
	unsigned short hazardSpeed;
	std::pair<unsigned int, unsigned int> gridSize;
	//The environment grid will have a number of numeric values which have different meanings.
	/*	0 = empty cell/tile 
		1 = impassible terrain
		2 = interactable object (may be replaced with the interactable object)
		3 = agent (may be replaced with the agent object)
		4 = hazard 
	*/
	//These values are used in conjunction with other member functions to find the object which has the matching position.
	std::vector<std::vector<unsigned int>> environmentGrid;
	sf::VertexArray renderedGrid;
	sf::VertexArray renderedInter;
};

#endif // !ENVIRONMENT_H
