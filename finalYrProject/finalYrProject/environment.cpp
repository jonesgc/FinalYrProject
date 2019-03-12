#include "environment.h"



Environment::Environment()
{
}

//The environment grid is created of the requested size using 0s to represent blank tiles.
Environment::Environment(unsigned int x, unsigned int y)
{
	unsigned int row = x;
	unsigned int col = y;
	
	gridSize.first = x;
	gridSize.second = y;

	environmentGrid.resize(row);
	for (int i = 0; i < row; i++)
	{
		environmentGrid[i].resize(col);
		for (int j = 0; j < col; j++)
		{
			environmentGrid[i][j] = 0;
		}
	}
}

Environment::~Environment()
{
}

std::vector<std::vector<unsigned int>> Environment::getEnvironmentGrid()
{
	return environmentGrid;
}

sf::VertexArray Environment::getRenderedGrid()
{
	return renderedGrid;
}

std::pair<unsigned int, unsigned int> Environment::getGridSize()
{
	return gridSize;
}

sf::VertexArray Environment::getRenderedInter()
{
	return renderedInter;
}

void Environment::setRenderedGrid(sf::VertexArray g)
{
	renderedGrid = g;
}

void Environment::setRenderedInter(sf::VertexArray inter)
{
	renderedInter = inter;
}

void Environment::changeTile(unsigned int x, unsigned int y, unsigned short code)
{
	environmentGrid[x][y] = code;
}
