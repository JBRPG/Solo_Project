#pragma once

#include <stack>
#include <vector>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>


class Game{

private:
	sf::Vector2i gameDisplay{800, 600};
	int          gameFrameLimit{ 60 };

public:

	sf::RenderWindow window;

	//void pushState();
	//void popState();
	// void changeState();
	// State* peekstate();

	void gameLoop();

	sf::Vector2i getDisplay() { return gameDisplay; };
	int getFrameLimit()       { return gameFrameLimit; };

	Game();
	~Game();
};