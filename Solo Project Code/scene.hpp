#pragma once

#include <SFML\Graphics.hpp>

#include <memory>
#include <vector>

#include "game.hpp"
#include "entity.hpp"

class Game; // forward declare

class Scene{
private:

	std::vector<Entity*> EntityList;

public:

	Game* game;


	virtual void draw(sf::Time dt) = 0;
	virtual void update(sf::Time dt) = 0;

	virtual void addEntity(Entity*);
	virtual void removeEntity(Entity*);


};