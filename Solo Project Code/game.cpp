#include "game.hpp"

Game::Game(){

	this->window.create(sf::VideoMode (800,600), "Solo Project Ver 0.0");
	this->window.setFramerateLimit(60);
}

Game::~Game(){

	// Will pop remaining states

}

void Game::gameLoop(){
	sf::Clock clock;

	while (this->window.isOpen()){
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		// Update the user input
		// update whatever entity is in active scene
		this->window.clear(sf::Color::Black);
		// draw the entities within the active scene
		this->window.display();

	}

}