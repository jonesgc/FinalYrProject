#pragma once
#include <SFML/Graphics.hpp>

class GUI : public sf::Drawable, public sf::Transformable
{
public:
	bool initGUI();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray gui_vertices;
};

