#ifndef ABMSIMULATOR_H
#define ABMSIMULATOR_H

/*! \file abmSimulator.h
Author: Gregory Jones
Version: 0.1
\brief  Class header file. Core class of the program, containing the: main program loop (run()), event loop and render loop.
*/

/*
	\fn
	\brief
	\param
*/

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <tuple>
#include <algorithm>
#include <math.h>

#include "agent.h"
#include "interactable.h"
#include "crowd.h"
#include "statistics.h"
#include "environment.h"


class abmSimulator
{
public:
	abmSimulator();
	~abmSimulator();

	//Getters.
	sf::VertexArray getEditorOutline();

	//Setters.
	void setAgentContainer(std::vector<agent>);
	void setEditorOutline(sf::VertexArray);

	/*
	\fn int run()
	\breif The run function is the main loop of the program, so it contains the SFML render loop, SFML and TGUI event loop and the main program loop.
	\param Takes no parmeters but utilises various member variables.
	*/
	int run();

	/*
	\fn void mainScreenGUI(tgui::Gui&)
	\brief Creates the GUI elements and widgets of the "main" screen which is what the user sees when they first start the program.
	\param Gui& - a pointer to the GUI is required as input for the various TGUI methods within this function.

	*/
	void mainScreenGUI(tgui::Gui& gui);

	/*
	\fn void createSimulationScreen(tgui::Gui&)
	\brief Creates the screen for building a new simulation when the new simulation button is pressed.
	\param Gui& - a pointer to the GUI is required as input for the various TGUI methods within this function.
	*/
	void createSimulationScreen(tgui::Gui& gui);

	void createSimulationSaveFile();
	void createStatisticsFile();

	/*
	\fn loadSimulation()
	\brief Loads a JSON file, which must be in the correct format, into the program then calls createSimulation() with the read in values as parameters. 
			This does require a path to be fed into the function, but this will come from a GUI element.
	*/
	void loadSimulation();

	/*
	\fn void createSimulation(unsigned int, unsigned int, std::vector<agent>, std::vector<std::pair<unsigned int, unsigned int>>, std::vector<interactable>);
	\brief Sets up a the various member variables and containers (for both the rendered and "data" elements) that a simulation needs to function, this function is called after a simluation setup file has been read in.
	\param gridX The number of rows in the environment.
	\param gridY The number of columns in the environment.
	\param agentList vector of agents to be copied into the member variable agentContainer.
	\param terrain Contains the vertices coordinates for the the creation of terrain, note terrain is created using Bresenhams line algorithm and so the co-ordinates input here are the start and end of the line.
	\param interactables Contains the various interactable entities that need to be read into the environment grid.
	*/
	void createSimulation(unsigned int, unsigned int, std::vector<agent>, std::vector<std::pair<unsigned int, unsigned int>>, std::vector<interactable>);

	/*
	\fn runSimulation()
	\brief This function is called periodically by run() and it is used to perform the simulation logic: such as moving agents, updating states or expanding the hazard.
	*/
	void runSimulation();

	/*
	\fn loadSimulation()
	\brief When the load simulation button on the mainScreen is pressed this function is called that would take the input of a file path then loads the file. Note the file must be in the specific JSON format as documented.
	@see simulationFile
	*/
	std::vector<sf::CircleShape>drawAgents();

	/*
	\fn isValidCell(int, int)
	\brief Checks if the input co-ordinates are within the bounds of the two dimentional vector being used as the "grid".
	\param x co-ordinate
	\param y co-ordinate
	*/
	bool isValidCell(int,int);

	/*
	\fn bresenhamLine(Environment, unsigned int, unsigned int, unsigned int, unsigned int, unsigned short)
	\brief Draws a line from input co-ordinates to target co-ordinates on the input environment. "Draws" or rather replaces the values on the grid of the object code input.
			This code was adapted from:
	\param environment The environment to "draw" the line on.
	\param startX the X co-ordinate of the starting vertex.
	\param startY the Y co-ordiniate of the starting vertex.
	\param targetX the X co-ordinate of the target or end vertex.
	\param targetY the Y co-ordinate of the target or end vertex.
	\param objCode the value with which to change the tiles on the grid through the course of the line.
	*/
	Environment bresenhamLine(Environment,unsigned int, unsigned int, unsigned int, unsigned int, unsigned short);

	/*
	\fn BFSforCell(Environment, agent, unsigned short)
	\brief This is a breadth first search algorithm that searches the grid looking for the input target value and returns its location.
			This code was adapted from:
	\param environment the environment to perform the BFS on.
	\param agent this agent is used as the starting point for the BFS search.
	\param objCode the value that the BFS stops when it finds on the grid and returns its (X,Y) position.
	*/
	std::pair<unsigned int, unsigned int> BFSforCell(Environment, agent, unsigned short);
	

private:
	Environment environment;
	std::vector<agent> agentContainer;
	std::vector<interactable> interactableContainer;
	std::vector<crowd> crowdContainer;
	std::vector<agent> escapedAgentsContainer;
	std::vector<agent> casualtiesContainer;
	sf::VertexArray editorOutline;
	bool init;
	bool simReady;
};

#endif // !ABMSIMULATOR_H



