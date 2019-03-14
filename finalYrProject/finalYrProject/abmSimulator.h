#ifndef ABMSIMULATOR_H
#define ABMSIMULATOR_H

/*! \file abmSimulator.h
Author: Gregory Jones
Version: 0.1
\brief  Class header file. Core class of the program, containing the: main program loop (run()), event loop and render loop.
*/

/*
	\fn int run()
	\breif The run function is the main loop of the program, so it contains the SFML render loop, SFML and TGUI event loop and the main program loop.
	\param Takes no parmeters but utilises various member variables.
*/

/*
	\fn void mainScreenGUI(tgui::Gui&)
	\brief Creates the GUI elements and widgets of the "main" screen which is what the user sees when they first start the program.
	\param Gui& - a pointer to the GUI is required as input for the various TGUI methods within this function.

*/

/*
	\fn void createSimulationScreen(tgui::Gui&)
	\brief Creates the screen for building a new simulation when the new simulation button is pressed.
	\param Gui& - a pointer to the GUI is required as input for the various TGUI methods within this function.
*/

/*
	\fn void createSimulation(unsigned int, unsigned int, std::vector<agent>, std::vector<std::pair<unsigned int, unsigned int>>, std::vector<interactable>);
	\brief Sets up a the various member variables and containers (for both the rendered and "data" elements) that a simulation needs to function, this function is called after a simluation setup file has been read in.
	\param gridX The number of rows in the environment.
	\param gridY The number of columns in the environment.
	\param agentList vector of agents to be copied into the member variable agentContainer.
	\param terrain Contains the vertices coordinates for the the creation of terrain, note terrain is created using Bresenhams line algorithm and so the co-ordinates input here are the start and end of the line.
	\param interactables Contains the various interactable entities that need to be read into the environment grid.
*/

/*
	\fn runSimulation()
	\brief This function is called periodically by run() and it is used to perform the simulation logic: such as moving agents, updating states or expanding the hazard.
*/

/*
	\fn loadSimulation()
	\brief When the load simulation button on the mainScreen is pressed this function is called that would take the input of a file path then loads the file. Note the file must be in the specific JSON format as documented.
	@see simulationFile
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


	int run();
	void mainScreenGUI(tgui::Gui& gui);
	void createSimulationScreen(tgui::Gui& gui);

	void createSimulationSaveFile();
	void createStatisticsFile();
	void loadSimulation();

	void createSimulation(unsigned int, unsigned int, std::vector<agent>, std::vector<std::pair<unsigned int, unsigned int>>, std::vector<interactable>);
	void runSimulation();
	std::vector<sf::CircleShape>drawAgents();
	bool isValidCell(int,int);
	Environment bresenhamLine(Environment,unsigned int, unsigned int, unsigned int, unsigned int, unsigned short);
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



