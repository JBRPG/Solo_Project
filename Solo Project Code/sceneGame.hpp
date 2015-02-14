#pragma once

#include <SFML\Graphics.hpp>

#include "scene.hpp"
#include "game.hpp"

class SceneGame : public Scene{
private:

	sf::View  background1View;
	sf::View  background2View;
	sf::View  gameView;
	sf::View  playerView;
	sf::View  hudView;

public:
	SceneGame(Game* game);

	virtual void draw(sf::Time dt);
	virtual void update(sf::Time dt);

};