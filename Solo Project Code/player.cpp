#include "player.hpp"

void Player::update(float dt){
	this->movePlayer();
	this->shootPlayer();

}


/*
  For barebones purposes,
  we only focus on movement through keyboard arrows
*/
void Player::movePlayer(){

	float sqrt2 = 1.41;
	bool dirArray[4] = {false, false, false, false};

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
}

// We will create a bullet entity from the player later
void Player::shootPlayer(){


}