#ifndef ABMSIMULATOR_H
#define ABMSIMULATOR_H

/*
Author: Gregory Jones
Version: 0.1
Purpose: This is the file containing the definition of member variables and methods of the namesake class. This class can be considered of the program.
		This file will also contain the comments that will be used with doxygen to produce a form of documentation.
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

	int run();
	void mainScreenGUI(tgui::Gui& gui);
	void createSimulationScreen(tgui::Gui& gui);

	void createSimulationSaveFile();
	void createStatisticsFile();

	void createSimulation(unsigned int, unsigned int, std::vector<agent>, std::vector<std::pair<unsigned int, unsigned int>>, std::vector<interactable>);
	void runSimulation();
	void loadSimulation();

	sf::VertexArray getEditorOutline();
	void setEditorOutline(sf::VertexArray);

	std::vector<sf::CircleShape>drawAgents();
	bool isValidCell(int,int);
	Environment bresenhamLine(Environment,unsigned int, unsigned int, unsigned int, unsigned int, unsigned short);
	std::pair<unsigned int, unsigned int> BFSforCell(Environment, agent, unsigned short);
	void setAgentContainer(std::vector<agent>);
private:
	Environment environment;
	std::vector<agent> agentContainer;
	std::vector<interactable> interactableContainer;
	std::vector<crowd> crowdContainer;
	std::vector<agent> escapedAgentsContainer;
	std::vector<agent> casualtiesContainer;
	sf::VertexArray editorOutline;
	bool init;
};

#endif // !ABMSIMULATOR_H



