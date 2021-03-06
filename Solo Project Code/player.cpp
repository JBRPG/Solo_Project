#include "player.hpp"

#include "pickup.hpp"



void Player::update(float dt){
	this->movePlayer();
	this->shootPlayer(dt);
	this->checkHealthPlayer();

}


/* 
   For all entity comparisons, we will use dynamic_cast
   with the reference to Entity object - Entity& other
   to keep code cleaner

   dynamic_cast to a pointer type returns NULL if the cast fails
   dynamic_cast to a reference type would throw an exception on failure
*/

void Player::collideWith(Entity& other){
	
	// Check if the entity is Enemy
	if (Enemy* enemy = dynamic_cast<Enemy*>(&other)){
		// Take damage from enemy
		// unless invincible
		--this->health;
	}
	// Check if the entity is Bullet
	else if (Bullet* bullet = dynamic_cast<Bullet*>(&other)){
		if (!bullet->getEnemyShot()) return;

		// Take damage from bullet,
		// unless invincible
		--this->health;
	}
	else if (Pickup* pickup = dynamic_cast<Pickup*> (&other)){
		this->setWeapon(pickup->giveWeapon());
	}
}


/*
  For barebones purposes,
  we only focus on movement through keyboard arrows
*/
void Player::movePlayer(){

	float sqrt2 = 1.41;
	bool dirArray[4] = { false, false, false, false };

	// The following firections are in order:
	// left, up, right, down

	if (Input::instance()->pressKeybutton(sf::Keyboard::Left))
		dirArray[0] = true;
	if (Input::instance()->pressKeybutton(sf::Keyboard::Up))
		dirArray[1] = true;
	if (Input::instance()->pressKeybutton(sf::Keyboard::Right))
		dirArray[2] = true;
	if (Input::instance()->pressKeybutton(sf::Keyboard::Down))
		dirArray[3] = true;

	sf::Vector2f velocity{ 0, 0 };

	velocity.x = this->speed * (dirArray[2] - dirArray[0]);
	velocity.y = this->speed * (dirArray[3] - dirArray[1]);

	if ((dirArray[0] || dirArray[2]) && (dirArray[1] || dirArray[3])){

		velocity.x /= sqrt2;
		velocity.y /= sqrt2;
	}

	// When I added the scroll speed to the move function,
	// I expected that the player ship would look like it stands still
	// however, the framerate is not constant and often below 60fps,
	// which causes the scrolling to go faster than the player

	this->move(velocity + myScene->getScrollSpeed()); // this for screen scrolling testing
	//this->move(velocity);

	// keep player from going out of bounds
	sf::Vector2f tl_window_view = myScene->game->window.mapPixelToCoords(
		sf::Vector2i(0,0));
	sf::Vector2f br_window_view = myScene->game->window.mapPixelToCoords(
		sf::Vector2i(myScene->game->window.getSize().x, myScene->game->window.getSize().x));

	if (this->getGlobalBounds().left < tl_window_view.x){
		this->setPosition(tl_window_view.x + this->getGlobalBounds().width / 2,
			this->getPosition().y);
	}
	if (this->getPosition().x >= br_window_view.x
		- this->getGlobalBounds().width/2){
		this->setPosition(br_window_view.x - this->getGlobalBounds().width / 2,
			this->getPosition().y);
	}
	if (this->getGlobalBounds().top < tl_window_view.y){
		this->setPosition(this->getPosition().x,
			tl_window_view.y + this->getGlobalBounds().height / 2);
	}
	if (this->getPosition().y >= br_window_view.y
		- this->getGlobalBounds().height / 2){
		this->setPosition(this->getPosition().x,
			br_window_view.y - this->getGlobalBounds().height / 2);
	}
}


void Player::shootPlayer(float dt){

	myWeapon->update(*this);

}

void Player::checkHealthPlayer(){
	if (this->health <= 0) myScene->storeRemovedEntity(this);
}
