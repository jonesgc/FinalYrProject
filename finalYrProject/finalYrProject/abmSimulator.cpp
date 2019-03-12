/*
Program Author: Gregory Jones.
File version: 0.1

Purpose: This file is the implementation of of the corsiponding header. It can be considered the "center" of the class structure, with only the wrapper "above" it in the hierachy.
		But because the wrapper, main.cpp, has no implementations or definitions and only serves to call the run function from within this file. Within this file are some of the most important
		methods, notably run which functions as the main program loop where IO events are handled. 

Note: Throughout this project code has be implemented from other sources, though almost always I have modifed or changed elements of its implementation, I have tried to credit the original author
		via the link that is above the code that I did not orignally write.
*/

#include "abmSimulator.h"

using std::vector;
using std::tuple;
using std::pair;
using std::queue;

//For convience with 3rd party JSON libary
using json = nlohmann::json;

abmSimulator::abmSimulator()
{

}


abmSimulator::~abmSimulator()
{
}

//This is the main "loop" of the program, it contains the event loop for both the GUI and SFML.
//Within this function the GUI screens will be created and the widgets will be connected to functions that execute the ABM functionality
int abmSimulator::run()
{
	//Settings initalisation. Currently using antialiasing.
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//Create window (x,y)size, if using the windowed mode, with title and load the settings.
	sf::RenderWindow window(sf::VideoMode(1900, 980), "project", sf::Style::Default, settings);

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(250.f, 0.f)),
		sf::Vertex(sf::Vector2f(250.f, 980.f))
	};


	//This should be made relative to the program window.
	sf::VertexArray e(sf::LineStrip, 5);
	e[0].position = sf::Vector2f(260.f, 50.f);
	e[1].position = sf::Vector2f(1800.f, 50.f);
	e[2].position = sf::Vector2f(1800.f, 900.f);
	e[3].position = sf::Vector2f(260.f, 900.f);
	e[4].position = sf::Vector2f(260.f, 50.f);

	this->setEditorOutline(e);
	tgui::Gui gui{ window };


	//This block tries to create the "main screen" GUI elements, the program ends if it fails.
	try
	{
		mainScreenGUI(gui);
	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "Creation of mainScreenGUI failed." << e.what() << std::endl;
		return 1;
	}
	
	//Program loop.
	while (window.isOpen())
	{
		//Check all the events that happened since the last iteration of the loop.
		sf::Event event;
		while (window.pollEvent(event))
		{
			//If the red x pressed.
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			gui.handleEvent(event);
		}

		//Recommended render loop for SFML.
		window.clear();
		gui.draw();
		window.draw(line, 2, sf::Lines);
		window.draw(this->editorOutline);
		window.draw(environment.getRenderedGrid());
		window.draw(environment.getRenderedInter());

		//Draw the agents.
		vector<sf::CircleShape> tempAgents = drawAgents();
		if(tempAgents.size() > 0)
		{
			for each (sf::CircleShape s in tempAgents)
			{
				window.draw(s);
			}
		}
		window.display();
	}

	return 0;
}


//Creates the GUI elements for the main screen, much of the prototypes functionality can be accessed from this screen.
void abmSimulator::mainScreenGUI(tgui::Gui & gui)
{
	
	tgui::Button::Ptr newSim = tgui::Button::create();
	newSim->setSize({ "130", "30" });
	newSim->setPosition({ "3%", "3%" });
	newSim->setText("New Simulation");
	gui.add(newSim);

	tgui::Button::Ptr loadSim = tgui::Button::create();
	loadSim->setSize({ "130", "30" });
	loadSim->setPosition({ "3%", "6%" });
	loadSim->setText("Load Simulation");
	gui.add(loadSim);

	
	tgui::Button::Ptr runSim = tgui::Button::create();
	runSim->setSize({ "130", "30" });
	runSim->setPosition({ "3%", "90%" });
	runSim->setText("Simulate");
	gui.add(runSim);

	//Button actions.
	runSim->connect("pressed", &abmSimulator::runSimulation, this);
	loadSim->connect("pressed", &abmSimulator::loadSimulation, this);
}


void abmSimulator::createSimulationScreen(tgui::Gui & gui)
{
	tgui::Label::Ptr labelGridInput = tgui::Label::create();
	labelGridInput->setPosition({ "3%", "48%" });
	labelGridInput->setText("Input grid size");
	labelGridInput->setTextSize(14);
	labelGridInput->getRenderer()->setTextColor(sf::Color::White);
	gui.add(labelGridInput);

	tgui::Label::Ptr labelInputX = tgui::Label::create();
	labelInputX->setPosition({ "2%", "50%" });
	labelInputX->setText("X ");
	labelInputX->setTextSize(14);
	labelInputX->getRenderer()->setTextColor(sf::Color::White);
	gui.add(labelInputX);

	tgui::Label::Ptr labelInputY = tgui::Label::create();
	labelInputY->setPosition({ "2%", "52%" });
	labelInputY->setText("Y ");
	labelInputY->setTextSize(14);
	labelInputY->getRenderer()->setTextColor(sf::Color::White);
	gui.add(labelInputY);

	tgui::EditBox::Ptr inputX = tgui::EditBox::create();
	inputX->setPosition({ "3%","50%" });
	inputX->setSize({ "50", "25" });
	inputX->setDefaultText("0");
	gui.add(inputX);

	tgui::EditBox::Ptr inputY = tgui::EditBox::copy(inputX);
	inputY->setPosition({ "3%", "52%" });
	gui.add(inputY);
}

void abmSimulator::createSimulation(unsigned int gridX, unsigned int gridY, 
	vector<agent> agentList, vector<pair<unsigned int, unsigned int>> terrain, vector<interactable> interactList)
{
	//Create an environment grid of x y size.
	Environment newEnvironment(gridX, gridY);
	

	//Place the agents on the grid.
	//The hardcoded value of 3 is meant to represent the agent on the "data" grid.
	for each (agent a in agentList)
	{
		newEnvironment.changeTile(a.getPosition().first, a.getPosition().second, 3);
	}
	
	sf::VertexArray inters(sf::Quads);

	//Prepare the grid for rendering on the screen inside the editor view. Even though the user wont be able to edit it yet it will help visual debugging.
	sf::VertexArray grid(sf::Lines);
	float sx,sy,ex,ey,cell = 0;
	sx = 300.f;
	sy = 60.f;
	ex = 1700.f;
	ey = 890.f;
	cell = 15.f;

	//These variables are "temporary" and are used in the drawing of the grid so the oringial values are not changed. 
	float tx, ty = 0;
	tx = sx;
	ty = sy;

	//This is used to create the lines of the grid, depending on the value of the bool the vertex will be either the start or the end
	bool posW = true;
	bool posH = true;
	for (size_t i = 0; i < (gridX*2); i++)
	{
		//Horizontals
		if (posW)
		{
			grid.append(sf::Vertex(sf::Vector2f(sx, ty), sf::Color::Red));
			posW = false;
		}
		else
		{
			grid.append(sf::Vertex(sf::Vector2f(ex, ty), sf::Color::Red));
			posW = true;
			ty += cell;
		}
		
	}

	//Verticals
	for (size_t j = 0; j < (gridY*2); j++)
	{
		if (posH)
		{
			grid.append(sf::Vertex(sf::Vector2f(tx, sy), sf::Color::Red));
			posH = false;
		}
		else
		{
			grid.append(sf::Vertex(sf::Vector2f(tx, ey), sf::Color::Red));
			posH = true;
			tx += cell;
		}
	}

	//Set the Render position agents on the rendered grid.
	//The starting point of the rendered grid is (sx,sy) which is also (0,0) for the data grid.
	for each (agent a in agentList)
	{
		float rX, rY = 0;
		pair<unsigned int, unsigned int> gridDest = a.getPosition();

		rX = sx + (gridDest.first * cell);
		rY = sy + (gridDest.second * cell);

		a.setRposition(rX, rY);
	}

	
	//Draw the interactables on the rendered Grid.
	for each(interactable inter in interactList)
	{
		float rX, rY = 0;
		pair<unsigned int, unsigned int> gridDest = inter.getPosition();

		rX = sx + (gridDest.first * cell);
		rY = sy + (gridDest.second * cell);

		grid.append(sf::Vertex(sf::Vector2f(rX, rY), sf::Color::Magenta));
		grid.append(sf::Vertex(sf::Vector2f(rX, rY+15), sf::Color::Magenta));
		grid.append(sf::Vertex(sf::Vector2f(rX+15, rY+15), sf::Color::Magenta));
		grid.append(sf::Vertex(sf::Vector2f(rX+15, rY), sf::Color::Magenta));
		
	}

	environment.setRenderedInter(inters);

	//Draw the terrain
	bool flag1, flag2 = false;
	unsigned int stX, stY, etX, etY = 0;

	//Since the terrain are lines each line requires a start and an end vertex.
	for (auto i = 0; i < terrain.size(); i++)
	{
		//Add the value of 2 (denoting terrain) to "data" grid.
		if (i % 2 == 0)
		{
			stX = terrain.at(i).first;
			stY = terrain.at(i).second;

			//Add the line to the rendered grid - this is to save time for the prototype its should be its own structure for tidyness.
			float rX = sx + (stX * cell);
			float rY = sy + (stY * cell);
			grid.append(sf::Vertex(sf::Vector2f(rX, rY), sf::Color::Green));

			flag1 = true;
		}
		else
		{
			etX = terrain.at(i).first;
			etY = terrain.at(i).second;

			//Add the line to the rendered grid - this is to save time for the prototype its should be its own structure for tidyness.
			float rX = sx + (etX * cell);
			float rY = sy + (etY * cell);
			grid.append(sf::Vertex(sf::Vector2f(rX, rY), sf::Color::Green));

			flag2 = true;
		}
		
		if (flag1 && flag2)
		{
			bresenhamLine(newEnvironment,stX, stY, etX, etY);
			flag1, flag2 = false;
		}
	}
	

	//Envrionment is created and ready for simulation.
	newEnvironment.setRenderedGrid(grid);
	agentContainer = agentList;
	this->environment = newEnvironment;
}


//Load the given simulation file via the path and run the creation of the simulation.
//Code for opening and reading a JSON file adapted from: https://github.com/nlohmann/json
void abmSimulator::loadSimulation()
{
	std::ifstream file;
	std::string path = "test.txt";

	json j;
	json jEnv;
	json jAgents;
	json jTerrain;
	json jInteractable;

	unsigned int gridX=0;
	unsigned int gridY=0;
	vector<agent> agentList;
	vector<interactable> interactableList;
	vector<pair<unsigned int, unsigned int>> terrain;
	json item;

	//Get the path for opening the file.
	file.open("D:\\dev\\project\\test.json");
	if (file.is_open()) 
	{
		//The prototype will only feature very basic error checking of the JSON.
		//Read in the size of the environment
		file >> j;
		jEnv = j.at("environment");
		gridX = jEnv.at("gridX");
		gridY = jEnv.at("gridY");
		jTerrain = jEnv.at("terrain");

		//Read in terrain.
		if (jTerrain.size() > 0)
		{
			for (auto it = jTerrain.begin(); it != jTerrain.end(); it++)
			{
				item = it.value();
				//Since the terrain can be considered lines the coords read in are the coords for the start and end vertices.
				int stX, stY, etX, etY = 0;
				stX = item.at(0);
				stY = item.at(1);
				etX = item.at(2);
				etY = item.at(3);

				//Add the vertices to the terrain container.
				terrain.push_back(std::make_pair(stX, stY));
				terrain.push_back(std::make_pair(etX, etY));
			}
		}

		//Read in the agents.
		int count = 1;
		jAgents = j.at("agents");
		if (jAgents.size() > 0)
		{
			for (auto it = jAgents.begin(); it != jAgents.end(); it++)
			{
				item = it.value();
				unsigned int xPos = item.at(0);
				unsigned int yPos = item.at(1);
				bool coOp = item.at(2);
				std::string sex = item.at(3);
				unsigned int age = item.at(4);
				agentList.push_back(agent(count, xPos, yPos, coOp, sex, age));
				count++;
			}
		}

		//Read in the interactables.
		//int count = 1;
		jInteractable = jEnv.at("interactables");
		if (jInteractable.size() > 0)
		{
			for (auto it = jInteractable.begin(); it != jInteractable.end(); it++)
			{
				item = it.value();
				unsigned int xPos = item.at(0);
				unsigned int yPos = item.at(1);
				std::string descr = item.at(2);
				bool state = item.at(3);
				unsigned short intgre = item.at(4);
				unsigned short heatr = item.at(5);
				interactableList.push_back(interactable(count,xPos, yPos, descr,state,intgre,heatr));
				count++;
			}
		}
		
		file.close();
	}

	//Create the simulation with the loaded values.
	createSimulation(gridX, gridY, agentList, terrain, interactableList);
}

sf::VertexArray abmSimulator::getEditorOutline()
{
	return editorOutline;
}

void abmSimulator::setEditorOutline(sf::VertexArray input)
{
	editorOutline = input;
}

vector<sf::CircleShape> abmSimulator::drawAgents()
{
	vector<sf::CircleShape>agentSprites;

	//These are variables for where the start of the rendered grid corner is.
	float sx = 300.f;
	float sy = 60.f;

	//This is the size of the cell.
	float cell = 15.f;

	//Iterate through the agent container and create a circle shape in the right position.
	//There will be a similar function inside the crowd class that performs this as well.
	for each (agent a in agentContainer)
	{
		float rX, rY = 0;
		pair<unsigned int, unsigned int> gridDest = a.getPosition();

		rX = sx + (gridDest.first * cell);
		rY = sy + (gridDest.second * cell);

		a.setRposition(rX, rY);
		sf::CircleShape sprite;
		sprite.setRadius(5);
		sprite.setFillColor(sf::Color::Blue);
		sprite.setPosition(rX, rY);

		agentSprites.push_back(sprite);
	}

	return agentSprites;
}

//This function was adapted from https://www.geeksforgeeks.org/shortest-path-in-a-binary-maze/ as part of the BFS implementation.
bool abmSimulator::isValidCell(int r, int c)
{
	return (r >= 0) && (r < environment.getGridSize().first) && (c >= 0) && (c < environment.getGridSize().second);
}

//bresenham algorithm code adapted from: http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B C++ section.
//This was to avoid the reinventing the square wheel.
void abmSimulator::bresenhamLine(Environment env,unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x < maxX; x++)
	{
		if (steep)
		{
			env.changeTile(y, x, 2);
		}
		else
		{
			env.changeTile(x, y, 2);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

pair<unsigned int, unsigned int> abmSimulator::BFSforCell(Environment env, agent a, unsigned short objCode)
{
	vector<vector<unsigned int>>gridImage = env.getEnvironmentGrid();
	unsigned int row = env.getGridSize().first;
	unsigned int col = env.getGridSize().second;
	vector<tuple<pair<unsigned int, unsigned int>, pair<unsigned int, unsigned int>>> path;
	pair<unsigned int, unsigned int> target;
	//BFS adapted from https://www.geeksforgeeks.org/shortest-path-in-a-binary-maze/.

	int rowNum[] = { -1, 0, 0, 1 };
	int colNum[] = { 0, -1, 1, 0 };


	//Get the agents position.
	pair<unsigned int, unsigned int> curPos = a.getPosition();
	unsigned int curX = curPos.first;
	unsigned int curY = curPos.second;

	//A queue containing the distance from the source (int) and the pair(x,y) location of the cell.
	queue < pair<int, pair<unsigned int, unsigned int>>> queue;
	pair<int, pair<unsigned int, unsigned int>> queueCell = std::make_pair(0, std::make_pair(curX, curY));
	queue.push(queueCell);

	path.push_back(std::make_tuple(std::make_pair(curX, curY), std::make_pair(curX, curY)));
	pair<unsigned int, unsigned int> parent = std::make_pair(curX, curY);

	//A vector containing all the vertices of the grid and whether they have been vistied.
	vector<vector<bool>> vistied;
	vistied.resize(row);
	for (int i = 0; i < row; i++)
	{
		vistied[i].resize(col);
		for (int j = 0; j < col; j++)
		{
			vistied[i][j] = false;
		}
	}

	//Mark the source cell as visited.
	vistied[a.getPosition().first][a.getPosition().second] = true;

	while (!queue.empty())
	{
		pair<int, pair<unsigned int, unsigned int>> currCell = queue.front();
		pair<unsigned int, unsigned int> currCellPos = currCell.second;

		//Look for the requested cell type.
		if (gridImage[currCellPos.first][currCellPos.second] == objCode)
		{
			//Found it.
			target = std::make_pair(currCellPos.first, currCellPos.second);
			return target;
		}

		queue.pop();

		for (int i = 0; i < 4; i++)
		{
			int curRow = currCellPos.first + rowNum[i];
			int curCol = currCellPos.second + colNum[i];

			if (isValidCell(curRow, curCol) && (vistied[curRow][curCol] == false) && (gridImage[curRow][curCol] == 0))
			{
				vistied[curRow][curCol] = true;
				pair<int, pair<unsigned int, unsigned int>>adjacentCell = std::make_pair(currCell.first + 1, std::make_pair(curRow, curCol));
				queue.push(adjacentCell);
				path.push_back(std::make_tuple(std::make_pair(curRow, curCol), parent));
				parent = std::make_pair(curRow, curCol);
			}
		}
	}

	return std::make_pair(-1,-1);
}

void abmSimulator::runSimulation()
{	
	pair<unsigned int, unsigned int>target = std::make_pair(3, 3);
	long totalVertex = environment.getGridSize().first * environment.getGridSize().second;
	unsigned int row = environment.getGridSize().first;
	unsigned int col = environment.getGridSize().second;
	vector<vector<unsigned int>> gridImage = environment.getEnvironmentGrid();

	
	//Cant run a simulation with no agents in.
	if ((agentContainer.size() == 0)) 
	{
		//Need to produce an error message here.
	}
	else
	{
		//This update cycle is only for non-crowd agents. This function would need to be extended to work with crowds.
		for each (agent a in agentContainer)
		{
			unsigned int x = a.getPosition().first;
			unsigned int y = a.getPosition().second;
			unsigned short objCode = 3; 
			pair<unsigned int, unsigned int> target = BFSforCell(environment, a, objCode);

		}
	}
	
}