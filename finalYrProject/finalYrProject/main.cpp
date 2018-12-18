#include <SFML/Graphics.hpp>

#include "GUI.h"

int main()
{	
	//Settings initalisation. Currently using antialiasing.
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//Create window (x,y) with title and load the settings.
	sf::RenderWindow window(sf::VideoMode(600, 600), "project", sf::Style::Default, settings);

	GUI gui;
	gui.initGUI();

	

	//Program loop runs aslong as the window is open.
	while (window.isOpen())
	{
		//Check all the windows events that happened since the last iteration of the loop.
		sf::Event event;
		while (window.pollEvent(event))
		{
			//If the red x is pressed close the window and stop the program.
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}

		//Recommended render loop for SFML.
		window.clear();
		window.draw(gui);
		window.display();
	}

	return 0;
}