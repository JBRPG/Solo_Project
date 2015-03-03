#include "bullet.hpp"

void Bullet::collideWith(Player*){
	if (!enemyShot) return;

	// destroy the bullet
	// player health reduction taken care of
	// in Player's code

	std::cout << "Player Hit" << std::endl;

	// I am having trouble of enemy bullet not hitting player

	myScene->storeRemovedEntity(this);


}

void Bullet::collideWith(Enemy*){
	if (enemyShot) return;

	// destroy bullet
	// enemy health reduction in its own code

	std::cout << "Enemy Hit" << std::endl;

	// I am having trouble of player bullet not hitting enemy

	myScene->storeRemovedEntity(this);

}

void Bullet::update(float dt){

	// Since math functions take radians for sine and cosine,
	// we had to covnert from degrees to radians through the variables below

	float pi = 3.14;
	float deg_to_rad = pi / 180.0f;

	// Move the bullet with the given velocity (speed and rotation angle)
	this->move(speed * cos(this->getRotation() * deg_to_rad),
		       speed * sin(this->getRotation() * deg_to_rad));


}