#pragma once

#include <SFML\Graphics.hpp>

#include "scene.hpp"
#include "game.hpp"
#include "entity.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "collisionGrid.hpp"

class SceneGame : public Scene{
private:

	sf::View  background1View;
	sf::View  background2View;
	sf::View  gameView;
	sf::View  playerView;
	sf::View  hudView;

	// for temporary purpose, we will have a background sprite
	sf::Sprite background;
	Player* player;

	// Other important variables
	collisionGrid gridBox;


public:
	SceneGame(Game* game);

	// Scene functions
	virtual void draw(float dt);
	virtual void update(float dt);

	void populateGrid();
	void checkCollisions();

};