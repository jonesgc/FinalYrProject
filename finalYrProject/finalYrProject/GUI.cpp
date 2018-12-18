#include "GUI.h"

//Add the shapes of the gui to the vertex array.
bool GUI::initGUI()
{
	gui_vertices.resize(4);
	gui_vertices.setPrimitiveType(sf::Quads);

	gui_vertices[0].position = sf::Vector2f(10.f, 10.f);
	gui_vertices[1].position = sf::Vector2f(100.f, 10.f);
	gui_vertices[2].position = sf::Vector2f(100.f, 100.f);
	gui_vertices[3].position = sf::Vector2f(10.f, 100.f);
	
	return true;
}

void GUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(gui_vertices, states);
}



