#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include"SFML/Graphics.hpp"

#include <utility>
#include <vector>



//This class represents the environment that the simulation will take place in.
//Due to the possible sized of the environment grid this class should always be dynamically allocated.
class Environment
{
public:
	Environment();
	Environment(unsigned int, unsigned int);
	~Environment();
	
	//Getters and Setters.
	//The environment grid is created within the constructor.
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


	//This function will allow a "tile" value to be changed. This can be used in a number of functions.
	//For example this could be used to move an agent by changing the value from 0 (empty) to 3(agent)
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
