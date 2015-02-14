#include "sceneGame.hpp"

SceneGame::SceneGame(Game* game){


	// Set up the view layers

	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->background1View.setSize(pos);
	this->background2View.setSize(pos);
	this->gameView.setSize(pos);
	this->playerView.setSize(pos);
	this->hudView.setSize(pos);
	pos *= 0.5f;
	this->background1View.setCenter(pos);
	this->background2View.setCenter(pos);
	this->gameView.setCenter(pos);
	this->playerView.setCenter(pos);
	this->hudView.setCenter(pos);

	// We will fill in other things later
}

void SceneGame::draw(sf::Time dt){
	// draw the entities

}

void SceneGame::update(sf::Time){
	///update the entities

}