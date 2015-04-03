#include "player.hpp"



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
	this->move(velocity);

	// keep player from going out of bounds
	if (this->getGlobalBounds().left < 0){
		this->setPosition(this->getGlobalBounds().width / 2,
			this->getPosition().y);
	}
	if (this->getPosition().x >= myScene->game->window.getSize().x
		- this->getGlobalBounds().width/2){
		std::cout << "Global bound width: " << this->getGlobalBounds().width << std::endl;
		this->setPosition(myScene->game->window.getSize().x - this->getGlobalBounds().width / 2,
			this->getPosition().y);
	}
	if (this->getGlobalBounds().top < 0){
		this->setPosition(this->getPosition().x,
			this->getGlobalBounds().height / 2);
	}
	if (this->getPosition().y >= myScene->game->window.getSize().y
		- this->getGlobalBounds().height / 2){
		std::cout << "Global bound height: " << this->getGlobalBounds().height << std::endl;
		this->setPosition(this->getPosition().x,
			myScene->game->window.getSize().y - this->getGlobalBounds().height / 2);
	}
}

/*
   Since the player has to make bullets, then we need to add the bullets
   to the entity list

   We will add in a Weapon object to represent the weapon currently equipped


*/

// We will create a bullet entity from the player
// Will have delay period between each shot


void Player::shootPlayer(float dt){

	// we reduce time for shoot delay

	shootDelay --;

	if (shootDelay > 0) return;

	

	if (Input::instance()->pressKeybutton(sf::Keyboard::Space)){

		// Will replace a single bullet with Weapon,
		// which will take care of the bullet generation

		Bullet* bullet_p = new Bullet(myScene->game->texmgr.getRef("bulletPlayer"),
			1, 10, false, false, 0.0f);


		bullet_p->setPosition(this->getPosition().x + this->getGlobalBounds().width/2,
			this->getPosition().y);
		myScene->storeAddedEntity(bullet_p);
		bullet_p->setEnemyShot(false);

		resetDelay();
	}
}

void Player::checkHealthPlayer(){
	if (this->health <= 0) myScene->storeRemovedEntity(this);
}
