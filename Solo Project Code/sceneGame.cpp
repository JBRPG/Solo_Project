#include "sceneGame.hpp"
#include "input.hpp"


SceneGame::SceneGame(Game* game){

	this->game = game; // need this to run the game.

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

	// Initialize the background

	background = sf::Sprite(this->game->texmgr.getRef("background"));

	// Initialize the entities

	// for now we just add in the player and a few others
	// hardcoded until we make use of the random generator

	player = new Player(this->game->texmgr.getRef("playerSprite"),
		1, 5, false, 3);
	player->setPosition(sf::Vector2f(100, 300));

	addEntity(player);

	// We will fill in other things later
}

void SceneGame::draw(float dt){

	// draw the background
	this->game->window.setView(background1View);
	this->game->window.draw(background);

	// draw the entities
	
	//*

	// let's test this out for now....

	for (int i = 0; i < getEntitysize(); ++i){
		sf::Sprite* idxSprite = getEntity(i);
		this->game->window.draw(*idxSprite);
	}
	//*/

}

void SceneGame::update(float dt){
	///update the entities
	for (int i = 0; i < getEntitysize(); ++i){
		Entity* idxEntity = getEntity(i);
		idxEntity->update(dt);
	}
}