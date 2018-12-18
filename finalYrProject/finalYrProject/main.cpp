#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

void initGuiElem(tgui::Gui& gui);

int main()
{	
	//Settings initalisation. Currently using antialiasing.
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//Create window (x,y) with title and load the settings.
	sf::RenderWindow window(sf::VideoMode(800, 800), "project", sf::Style::Default, settings);

	tgui::Gui gui{ window };
	initGuiElem(gui);

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

			gui.handleEvent(event);
		}

		//Recommended render loop for SFML.
		window.clear();
		//window.draw();
		gui.draw();
		window.display();
	}

	return 0;
}

void initGuiElem(tgui::Gui & gui)
{
	tgui::Button::Ptr button = tgui::Button::create();
	button->setSize({ "50%", "16.67" });
	button->setPosition({ "25%", "70%" });
	gui.add(button);
}
