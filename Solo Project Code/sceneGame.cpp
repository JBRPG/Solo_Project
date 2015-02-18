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

/*
  These collision-based functions are responsible
  for managing all the entities on screen.
  
  populateGrid will place the entities at the appropriate cells.

  checkCollisions will compare entities within occupied cells.
  If the two unique entities actually collide, then do the collision
  work between the two.


*/

void SceneGame::populateGrid(){

	gridBox.reset();

	// Set up the rectangle to represent the cell.
	// Default is at top left corner
	sf::FloatRect cellRect = sf::FloatRect
		(sf::Vector2f(0,0),sf::Vector2f(
				game->window.getSize().x/gridBox.slicesX,
				game->window.getSize().y/gridBox.slicesY));

    // Now we check each 

	for (int i = 0; i <= getEntitysize(); ++i){
		for (auto x = 0; x < gridBox.slicesX; ++x){
			for (auto y = 0; y < gridBox.slicesY; ++y){

				// Set up the 4 corners for the cell's area
				cellRect.left = game->window.getSize().x * (x / gridBox.slicesX);
				cellRect.top = game->window.getSize().y * (y / gridBox.slicesY);
				cellRect.width = game->window.getSize().x * (x+1 / gridBox.slicesX);
				cellRect.height = game->window.getSize().y * (y+1 / gridBox.slicesY);


				// Add the entitiy to the cell if they touch
				if (getEntity(i)->getGlobalBounds().intersects(cellRect)){
					gridBox.append(x, y, getEntity(i));
				}

			}
		}

	}
}

void SceneGame::checkCollisions(){

	for (auto i = 0; i < gridBox.slicesX; ++i){
		for (auto j = 0; j < gridBox.slicesY; ++j){
			if (gridBox.cell[i][j].nEntities < 2) continue;

			for (auto k = 0; k < gridBox.cell[i][j].nEntities; ++k){
				for (auto l = 0; l < gridBox.cell[i][j].nEntities; ++l){

					// Set up the pointers and compare them
					auto p = gridBox.cell[i][j].items[k];
					auto q = gridBox.cell[i][j].items[l];
					if (p == q) continue; // we do not want the same pointer

					if (p->getGlobalBounds().
						intersects(q->getGlobalBounds() )){

						// Do a series of collisions depending on the sub-type of entity

					}


				}
			}
		}
	}

}

