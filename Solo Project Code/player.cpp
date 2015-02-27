#include "player.hpp"



void Player::update(float dt){
	this->movePlayer();
	this->shootPlayer(dt);
	this->checkHealthPlayer();

}

void Player::collideWith(Enemy* enemy){
	// Take damage from enemy
	// unless invincible
	--this->hp;
}

void Player::collideWith(Bullet* bullet){
	if (!bullet->getEnemyShot()) return;

	// Take damage from bullet,
	// unless invincible
	--this->hp;

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
*/

// We will create a bullet entity from the player
// Will have delay period between each shot


void Player::shootPlayer(float dt){

	// we reduce time for shoot delay

	shootDelay -= dt;

	if (shootDelay > 0.0f) return;

	

	if (Input::instance()->pressKeybutton(sf::Keyboard::Space)){

		


		///*

		Bullet* bullet_p = new Bullet(myScene->game->texmgr.getRef("bulletPlayer"),
			1, 10, false, false, 0.0f);


		bullet_p->setPosition(this->getPosition().x + this->getGlobalBounds().width/2,
			this->getPosition().y);
		myScene->storeAddedEntity(bullet_p);

		resetDelay();

		//*/


	}
}

void Player::checkHealthPlayer(){
	if (this->hp <= 0) myScene->storeRemovedEntity(this);
}
