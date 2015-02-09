#pragma once

#include "game.hpp"
#include <SFML\Graphics.hpp>

class Game; // forward declare

class State{
public:
	Game& game;

	virtual void draw(sf::Time dt) = 0;
	virtual void update(sf::Time dt) = 0;

};