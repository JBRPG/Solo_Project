#pragma once

#include "entity.hpp"

/*
The collision grid consist of two classes:

Grid:
It will divide the screen into set number of cells based on
the number of horizontal and vertical slices across the game screen.

Cell:
It stores the entities and is given a hard-coded limit to avoid dynamic allocation

The collision grid's cells get updated at every frame.

First we clear all the cells to 0 entities.
Next we scan the grid to add active entnties to each cell.
Then we check with pixel perfect collision to to remove any entity
that happens to be destroyed.

The cycle repeats.

*/

class collisionGrid{


public:
	collisionGrid();

	static const int slicesX = 5;
	static const int slicesY = 5;
	static const int maxEntities = 100;

	struct Cell{
		Entity* items[maxEntities];
		int nEntities;
	};

	Cell cell[slicesX][slicesY];

	void append(int, int, Entity*);
	void reset();


};